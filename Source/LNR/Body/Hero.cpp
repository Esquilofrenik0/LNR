#include "Hero.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LNR/Component/CombatComponent.h"
#include "LNR/Component/EquipmentComponent.h"

AHero::AHero()
{
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
	TurnRateGamepad = 50.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	TpArm = CreateDefaultSubobject<USpringArmComponent>("TpArm");
	TpArm->SetupAttachment(RootComponent);
	TpArm->TargetArmLength = 300.0f;
	TpArm->SetRelativeLocation(FVector(0, 25, 75));
	TpArm->bUsePawnControlRotation = true;
	TpCamera = CreateDefaultSubobject<UCameraComponent>("TpCamera");
	TpCamera->SetupAttachment(TpArm, USpringArmComponent::SocketName);
	TpCamera->bUsePawnControlRotation = false;
	TpCamera->SetActive(true);
	TpCamera->SetFieldOfView(90);
	FpCamera = CreateDefaultSubobject<UCameraComponent>("FpCamera");
	FpCamera->SetupAttachment(GetMesh(), "Camera");
	FpCamera->bUsePawnControlRotation = true;
	FpCamera->SetActive(false);
	FpCamera->SetFieldOfView(120);
	FirstPerson = false;
	Flashlight = CreateDefaultSubobject<USpotLightComponent>("Flashlight");
	Flashlight->SetupAttachment(FpCamera);
	Flashlight->SetVisibility(false);
	Flashlight->SetRelativeLocation(FVector(5, 0, 0));
	FlashlightActive = false;
}

void AHero::BeginPlay()
{
	Super::BeginPlay();
}

void AHero::Restart()
{
	Super::Restart();
	if (IsLocallyControlled())
	{
		GetWorldTimerManager().ClearTimer(ClientTickTimer);
		GetWorldTimerManager().SetTimer(ClientTickTimer, this, &AHero::ClientTick, 0.1, true);
	}
}

void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AHero::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AHero::MoveRight);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AHero::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AHero::LookUpAtRate);

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

	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AHero::StartDodge);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHero::StartInteract);
	PlayerInputComponent->BindAction("CycleCamera", IE_Pressed, this, &AHero::StartCycleCamera);
}

void AHero::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (HasAuthority()) RefreshPitch();
}

void AHero::ClientTick()
{
	CheckView();
}

void AHero::CheckView()
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
	if (FHitResult hit; UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, TraceTypeQuery1, true,
	                                                          toIgnore, EDrawDebugTrace::None, hit, true))
	{
		if (AActor* hitActor = hit.GetActor())
		{
			if (hitActor->Implements<UInteract>())
			{
				Inter = hitActor;
				Execute_OnShowInfo(Inter, this, true);
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
	SetAttackPressed(true);
	Attack();
}

void AHero::StopAttack()
{
	SetAttackPressed(false);
}

void AHero::StartBlock()
{
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
			// if (hitActor->Implements<IInteract>()) Execute_OnInteract(hitActor, this);
			// else if (Cast<AInstancedFoliageActor>(hitActor))
			// {
			// UGameplayStatics::ApplyPointDamage(hitActor, 1, GetActorLocation(), hit, GetController(),
			// this, UPickupDamage::StaticClass());
			// }
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
	if (WeaponSwapHeld && Combat->State == Idle) Equipment->WeaponSwap();
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

void AHero::StartCycleCamera()
{
	FirstPerson = !FirstPerson;
	ResetCamera();
}

void AHero::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AHero::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AHero::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHero::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
