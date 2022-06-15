#include "Hero.h"
#include "InstancedFoliageActor.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LNR/Component/AttributesComponent.h"
#include "LNR/Component/CombatComponent.h"
#include "LNR/Component/EquipmentComponent.h"
#include "LNR/Component/InventoryComponent.h"
#include "LNR/DamageType/PickupDamage.h"
#include "LNR/Game/HudBitloner.h"
#include "LNR/Game/Playor.h"
#include "LNR/Widget/ActionBarWidget.h"
#include "LNR/Widget/HudWidget.h"
#include "LNR/Widget/InventoryWidget.h"
#include "LNR/Widget/SlotWidget.h"
#include "FoliagePluginActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "LNR/Animator/AniHero.h"
#include "LNR/Component/CraftingComponent.h"
#include "LNR/Component/HeadSphereComponent.h"
#include "LNR/Component/NavigationComponent.h"
#include "LNR/Foliage/FoliageNode.h"
#include "LNR/Foliage/RockNode.h"
#include "LNR/Foliage/PickupNode.h"
#include "LNR/Foliage/TreeNode.h"
#include "LNR/Game/Bitloner.h"
#include "LNR/Widget/WorldMapWidget.h"

AHero::AHero()
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
	TurnRateGamepad = 50.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	Navigation = CreateDefaultSubobject<UNavigationComponent>("Navigation");
	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Crafting = CreateDefaultSubobject<UCraftingComponent>("Crafting");
	TpArm = CreateDefaultSubobject<USpringArmComponent>("TpArm");
	TpArm->SetupAttachment(RootComponent);
	TpArm->TargetArmLength = 300.0f;
	TpArm->SetRelativeLocation(FVector(0, 25, 75));
	TpArm->bUsePawnControlRotation = true;
	TpCamera = CreateDefaultSubobject<UCameraComponent>("TpCamera");
	TpCamera->SetupAttachment(TpArm, USpringArmComponent::SocketName);
	TpCamera->bUsePawnControlRotation = false;
	TpCamera->SetActive(true);
	TpCamera->SetFieldOfView(ThirdPersonFov);
	FpCamera = CreateDefaultSubobject<UCameraComponent>("FpCamera");
	FpCamera->SetupAttachment(GetMesh(), "Camera");
	FpCamera->bUsePawnControlRotation = true;
	FpCamera->SetActive(false);
	FpCamera->SetFieldOfView(FirstPersonFov);
	FirstPerson = false;
	Flashlight = CreateDefaultSubobject<USpotLightComponent>("Flashlight");
	Flashlight->SetupAttachment(FpCamera);
	Flashlight->SetVisibility(false);
	Flashlight->SetRelativeLocation(FVector(5, 0, 0));
	FlashlightActive = false;
	Respawns = false;

	Head->OnComponentBeginOverlap.AddDynamic(this, &AHero::OnHeadBeginOverlap);
	Head->OnComponentEndOverlap.AddDynamic(this, &AHero::OnHeadEndOverlap);
}

void AHero::OnHeadBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetCollisionProfileName() == "WaterBodyCollision")
	{
		Combat->SetState(Swimming);
		Movement->SetMovementMode(MOVE_Flying);
	}
}

void AHero::OnHeadEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex)
{
	if (OtherComp->GetCollisionProfileName() == "WaterBodyCollision")
	{
		Combat->SetState(Idle);
		Movement->SetMovementMode(MOVE_Walking);
	}
}

void AHero::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AHero::Restart()
{
	Super::Restart();
	AniHero = Cast<UAniHero>(Animator);
	Player = Cast<APlayor>(GetController());
	Player->Hero = this;
	if (AHUD* nHud = Player->GetHUD()) Player->Hud = Cast<AHudBitloner>(nHud);
	if (IsLocallyControlled())
	{
		GetWorldTimerManager().ClearTimer(ClientTickTimer);
		GetWorldTimerManager().SetTimer(ClientTickTimer, this, &AHero::ClientTick, 0.1, true);
	}
	if (HasAuthority())
	{
		GetWorldTimerManager().ClearTimer(ServerTickTimer);
		GetWorldTimerManager().SetTimer(ServerTickTimer, this, &AHero::ServerTick, 0.1, true);
	}
}

void AHero::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AHero::BeginPlay()
{
	Super::BeginPlay();
}

void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AHero::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHero::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AHero::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AHero::LookUpAtRate);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AHero::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AHero::TouchStopped);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AHero::StartAttack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AHero::StopAttack);
	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &AHero::StartBlock);
	PlayerInputComponent->BindAction("Block", IE_Released, this, &AHero::StopBlock);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AHero::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AHero::StopSprint);
	PlayerInputComponent->BindAction("WeaponSwap", IE_Pressed, this, &AHero::StartWeaponSwap);
	PlayerInputComponent->BindAction("WeaponSwap", IE_Released, this, &AHero::StopWeaponSwap);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AHero::StartReload);
	PlayerInputComponent->BindAction("Reload", IE_Released, this, &AHero::StopReload);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AHero::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AHero::StopCrouch);

	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AHero::StartDodge);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHero::StartInteract);
	PlayerInputComponent->BindAction("CycleCamera", IE_Pressed, this, &AHero::StartCycleCamera);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AHero::StartInventory);
	PlayerInputComponent->BindAction("Menu", IE_Pressed, this, &AHero::StartMenu);

	PlayerInputComponent->BindAction("Action1", IE_Pressed, this, &AHero::StartAction1);
	PlayerInputComponent->BindAction("Action1", IE_Released, this, &AHero::StopAction1);
	PlayerInputComponent->BindAction("Action2", IE_Pressed, this, &AHero::StartAction2);
	PlayerInputComponent->BindAction("Action2", IE_Released, this, &AHero::StopAction2);
	PlayerInputComponent->BindAction("Action3", IE_Pressed, this, &AHero::StartAction3);
	PlayerInputComponent->BindAction("Action3", IE_Released, this, &AHero::StopAction3);
	PlayerInputComponent->BindAction("Action4", IE_Pressed, this, &AHero::StartAction4);
	PlayerInputComponent->BindAction("Action4", IE_Released, this, &AHero::StopAction4);
}

void AHero::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (HasAuthority()) RefreshPitch();
}

void AHero::ServerTick() const
{
	Attributes->Regenerate(0.1);
}

void AHero::ClientTick()
{
	CheckView();
}

void AHero::CheckView()
{
	if (Controller)
	{
		FVector start;
		FRotator rot;
		Controller->GetPlayerViewPoint(start, rot);
		FVector end = start + (rot.Vector() * 1000.0f);
		TArray<AActor*> toIgnore;
		toIgnore.Add(this);
		if (Inter != nullptr)
		{
			Execute_OnShowInfo(Inter, this, false);
			Inter = nullptr;
		}
		Player->Hud->ShowInteractionIcon(false);
		if (FHitResult hit; UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, TraceTypeQuery1, true,
		                                                          toIgnore, EDrawDebugTrace::None, hit, true))
		{
			if (AActor* hitActor = hit.GetActor())
			{
				if (hitActor->Implements<UInteract>())
				{
					Inter = hitActor;
					Execute_OnShowInfo(Inter, this, true);
					Player->Hud->ShowInteractionIcon(true);
				}
				else if (Cast<AInstancedFoliageActor>(hitActor) || Cast<AFoliageNode>(hitActor))
				{
					Player->Hud->ShowInteractionIcon(true, EInteractionType::Foliage);
				}
			}
		}
	}
}

void AHero::ResetCamera()
{
	if (FirstPerson)
	{
		TpCamera->SetActive(false);
		FpCamera->SetActive(true);
	}
	else
	{
		FpCamera->SetActive(false);
		TpCamera->SetActive(true);
	}
}

void AHero::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AHero::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AHero::StartAttack()
{
	if (InputUi) return;
	SetAttackPressed(true);
	Attack();
}

void AHero::StopAttack()
{
	SetAttackPressed(false);
}

void AHero::StartBlock()
{
	if (InputUi) return;
	SetBlockPressed(true);
	Block();
}

void AHero::StopBlock()
{
	SetBlockPressed(false);
}

void AHero::StartSprint()
{
	SetSprintPressed(true);
	Sprint();
}

void AHero::StopSprint()
{
	SetSprintPressed(false);
}

void AHero::StartDodge()
{
	Dodge();
}

void AHero::StartInteract()
{
	FVector start;
	FRotator rot;
	Controller->GetPlayerViewPoint(start, rot);
	FVector end = start + (rot.Vector() * 1000.0f);
	FHitResult hit;
	TArray<AActor*> toIgnore;
	toIgnore.Add(this);
	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, TraceTypeQuery1, true,
	                                          toIgnore, EDrawDebugTrace::ForDuration, hit, true,
	                                          FLinearColor::Red, FLinearColor::Green, 1))
	{
		if (AActor* hitActor = hit.GetActor())
		{
			if (hitActor->Implements<UInteract>()) Execute_OnInteract(hitActor, this);
			else if (Cast<AInstancedFoliageActor>(hitActor) || Cast<AFoliageNode>(hitActor))
			{
				UGameplayStatics::ApplyPointDamage(hitActor, 1, GetActorLocation(), hit, GetController(),
				                                   this, UPickupDamage::StaticClass());
			}
		}
	}
}

void AHero::StartWeaponSwap()
{
	WeaponSwapHeld = true;
	GetWorldTimerManager().ClearTimer(WeaponSwapHeldTimer);
	GetWorldTimerManager().SetTimer(WeaponSwapHeldTimer, this, &AHero::StartHolster, 0.5);
}

void AHero::StopWeaponSwap()
{
	if (WeaponSwapHeld) TryWeaponSwap();
	WeaponSwapHeld = false;
	GetWorldTimerManager().ClearTimer(WeaponSwapHeldTimer);
}

void AHero::StartHolster()
{
	if (WeaponSwapHeld && Combat->State == Idle)
	{
		Equipment->Holster = !Equipment->Holster;
		Equipment->SetHolster(Equipment->Holster);
	}
	WeaponSwapHeld = false;
	GetWorldTimerManager().ClearTimer(WeaponSwapHeldTimer);
}

void AHero::StartReload()
{
	ReloadHeld = true;
	GetWorldTimerManager().ClearTimer(ReloadHeldTimer);
	GetWorldTimerManager().SetTimer(ReloadHeldTimer, this, &AHero::StartFlashlight, 0.5);
}

void AHero::StopReload()
{
	if (ReloadHeld && Combat->State == Idle) Reload();
	ReloadHeld = false;
	GetWorldTimerManager().ClearTimer(ReloadHeldTimer);
}

void AHero::StartCrouch()
{
	Crouch();
}

void AHero::StopCrouch()
{
	UnCrouch();
}

void AHero::StartFlashlight()
{
	if (ReloadHeld)
	{
		FlashlightActive = !FlashlightActive;
		Flashlight->SetVisibility(FlashlightActive);
	}
	ReloadHeld = false;
	GetWorldTimerManager().ClearTimer(ReloadHeldTimer);
}

void AHero::StartInventory()
{
	if (Player->Hud->HudWidget->InventoryWidget->IsVisible()) Player->Hud->ShowInventory(false);
	else Player->Hud->ShowInventory(true);
}

void AHero::StartMenu()
{
	if (Player->Hud->HudWidget->WorldMapWidget->IsVisible()) Player->Hud->ShowWorldMap(false);
	else Player->Hud->ShowWorldMap(true);
}

void AHero::StartAction1()
{
	Player->Hud->HudWidget->ActionBarWidget->Action1Slot->SetColorAndOpacity(FLinearColor(0, 1, 0, 1));
	if (BlockPressed) ActivateConsumable(0);
	else Action1();
}

void AHero::StopAction1()
{
	Player->Hud->HudWidget->ActionBarWidget->Action1Slot->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
}

void AHero::StartAction2()
{
	Player->Hud->HudWidget->ActionBarWidget->Action2Slot->SetColorAndOpacity(FLinearColor(0, 1, 0, 1));
	if (BlockPressed) ActivateConsumable(1);
	else Action2();
}

void AHero::StopAction2()
{
	Player->Hud->HudWidget->ActionBarWidget->Action2Slot->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
}

void AHero::StartAction3()
{
	Player->Hud->HudWidget->ActionBarWidget->Action3Slot->SetColorAndOpacity(FLinearColor(0, 1, 0, 1));
	if (BlockPressed) ActivateConsumable(2);
	else Action3();
}

void AHero::StopAction3()
{
	Player->Hud->HudWidget->ActionBarWidget->Action3Slot->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
}

void AHero::StartAction4()
{
	Player->Hud->HudWidget->ActionBarWidget->Action4Slot->SetColorAndOpacity(FLinearColor(0, 1, 0, 1));
	if (BlockPressed) ActivateConsumable(3);
	else Action4();
}

void AHero::StopAction4()
{
	Player->Hud->HudWidget->ActionBarWidget->Action4Slot->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
}

void AHero::TryWeaponSwap()
{
	if (Combat->State == Idle) Equipment->WeaponSwap();
}

void AHero::SetInputUi(bool val)
{
	InputUi = val;
	if (val)
	{
		Player->SetInputMode(FInputModeGameAndUI());
		Player->SetShowMouseCursor(true);
	}
	else
	{
		Player->SetInputMode(FInputModeGameOnly());
		Player->SetShowMouseCursor(false);
	}
}

void AHero::Aim(bool val)
{
	Combat->Aiming = val;
	Combat->SetAiming(val);
	SetFov(val);
}

void AHero::SetFov(bool aiming)
{
	if (HasAuthority()) ClientSetFov(aiming);
	else ExecuteSetFov(aiming);
}

void AHero::ClientSetFov_Implementation(bool aiming)
{
	ExecuteSetFov(aiming);
}

void AHero::ExecuteSetFov(bool aiming)
{
	if (aiming)
	{
		FpCamera->SetFieldOfView(FirstPersonFov - 15);
		TpCamera->SetFieldOfView(ThirdPersonFov - 15);
	}
	else
	{
		FpCamera->SetFieldOfView(FirstPersonFov);
		TpCamera->SetFieldOfView(ThirdPersonFov);
	}
}

void AHero::StartCycleCamera()
{
	FirstPerson = !FirstPerson;
	ResetCamera();
}

void AHero::TurnAtRate(float Rate)
{
	if (InputUi) return;
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AHero::LookUpAtRate(float Rate)
{
	if (InputUi) return;
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AHero::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		if (Combat->State == Climbing)
		{
			const FVector WorldDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Z);
			AddMovementInput(WorldDirection, Value);
			Attributes->Stamina -= 0.1;
		}
		else if (Combat->State == Swimming)
		{
			const FVector WorldDirection = GetControlRotation().Vector();
			AddMovementInput(WorldDirection, Value);
		}
		else
		{
			const FVector WorldDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(WorldDirection, Value);
		}
	}
}

void AHero::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector WorldDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(WorldDirection, Value);
		if (Combat->State == Climbing) Attributes->Stamina -= 0.1;
	}
}

void AHero::OnFoliageHarvested_Implementation(AActor* FoliageActor, const TArray<FFoliageRewardData>& Rewards)
{
	IFoliagePluginInterface::OnFoliageHarvested_Implementation(FoliageActor, Rewards);
	if (AFoliageNode* fol = Cast<AFoliageNode>(FoliageActor))
	{
		if (Cast<APickupNode>(fol))
		{
			// if (UAnimMontage* mont = Bitloner->HarvestingData.HarvestingMontage["Pickup"]) PlayMontage(mont);
		}
		else if (Cast<ARockNode>(fol))
		{
			if (UAnimMontage* mont = Bitloner->HarvestingData.HarvestingMontage["Rock"]) PlayMontage(mont);
		}
		else if (Cast<ATreeNode>(fol))
		{
			if (UAnimMontage* mont = Bitloner->HarvestingData.HarvestingMontage["Tree"]) PlayMontage(mont);
		}
		for (int i = 0; i < Rewards.Num(); i++)
		{
			const int amt = FMath::RandRange(Rewards[i].NumRewards.Min, Rewards[i].NumRewards.Max);
			if (TSubclassOf<UResource> r = Bitloner->HarvestingData.HarvestingReward[Rewards[i].RewardOnHarvest])
			{
				Inventory->Add(r.GetDefaultObject(), amt);
			}
			Player->Print("Harvested " + Rewards[i].RewardOnHarvest.ToString() + " x" + FString::FromInt(amt));
		}
	}
}
