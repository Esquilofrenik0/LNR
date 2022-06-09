#include "Body.h"

#include "Hero.h"
#include "NavigationInvokerComponent.h"
#include "Components/CapsuleComponent.h"
#include "LNR/LNR.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LNR/AI/Npc.h"
#include "LNR/Component/ActionComponent.h"
#include "LNR/Component/AttributesComponent.h"
#include "LNR/Component/CombatComponent.h"
#include "LNR/Component/FactionComponent.h"
#include "LNR/DamageType/MeleeDamage.h"
#include "LNR/Component/InfoComponent.h"
#include "LNR/Component/InventoryComponent.h"
#include "LNR/DamageType/RangedDamage.h"
#include "LNR/Data/Dropable.h"
#include "LNR/Game/Bitloner.h"
#include "LNR/Interactor/Tombstone.h"
#include "Net/UnrealNetwork.h"

ABody::ABody()
{
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	Action = CreateDefaultSubobject<UActionComponent>("Action");
	Action->SetIsReplicated(true);
	Action->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	Attributes = CreateDefaultSubobject<UAttributesComponent>("Attributes");
	Combat = CreateDefaultSubobject<UCombatComponent>("Combat");
	Respawns = true;
}

void ABody::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABody, Pitch);
	DOREPLIFETIME(ABody, MovementDirection);
	DOREPLIFETIME(ABody, Tombstone);
	DOREPLIFETIME(ABody, AttackPressed);
	DOREPLIFETIME(ABody, BlockPressed);
	DOREPLIFETIME(ABody, SprintPressed);
}

void ABody::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Combat->Setup(this);
}

void ABody::BeginPlay()
{
	Super::BeginPlay();
	Info->Init(Attributes);
}

void ABody::Restart()
{
	Super::Restart();
	Attributes->Init();
	RefreshAttributes();
	Action->InitAbilityActorInfo(this, this);
	if (HasAuthority()) Action->InitializeAbilities();
}

float ABody::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                        AActor* DamageCauser)
{
	if (Combat->State == Dead) return 0;
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ABody* attacker = Cast<ABody>(DamageCauser);
	if (attacker && Faction->Faction == Empire && Cast<AHero>(attacker)) attacker->Attributes->ChangeWanted(5);
	if (Npc)
	{
		if (Npc->Target == nullptr) Npc->TryTarget(attacker);
		Npc->StartUnderAttack();
	}
	EDamageType dt = Ranged;
	if (Combat->State == Blocking)
	{
		Attributes->ChangeStamina(-DamageAmount);
		DamageAmount = 0;
	}
	if (DamageEvent.DamageTypeClass == UMeleeDamage::StaticClass())
	{
		dt = Melee;
		if (Combat->State == Blocking)
		{
			if (attacker)
			{
				attacker->Combat->SetState(Reacting);
				attacker->PlayMontage(attacker->Combat->TakeDamageMontage);
				Combat->ResetCombo();
			}
		}
		else
		{
			Combat->SetState(Reacting);
			PlayMontage(Combat->TakeDamageMontage);
			Combat->ResetCombo();
		}
	}
	Attributes->ChangeHealth(-DamageAmount);
	ShowWorldDamage(DamageAmount, dt, GetActorLocation());
	if (Attributes->Health <= 0) Die();
	return DamageAmount;
}

void ABody::Attack() const
{
	if (Combat->State == Idle) Action->Execute(EAbilityInput::Attack);
}

void ABody::Sprint() const
{
	if (Combat->State == Idle) Action->Execute(EAbilityInput::Sprint);
}

void ABody::Dodge() const
{
	if (Combat->State == Idle) Action->Execute(EAbilityInput::Dodge);
}

void ABody::Block() const
{
	if (Combat->State == Idle) Action->Execute(EAbilityInput::Block);
}

void ABody::Reload() const
{
	if (Combat->State == Idle) Action->Execute(EAbilityInput::Reload);
}

void ABody::Action1() const
{
	if (Combat->State == Idle) Action->Execute(EAbilityInput::Action1);
}

void ABody::Action2() const
{
	if (Combat->State == Idle) Action->Execute(EAbilityInput::Action2);
}

void ABody::Action3() const
{
	if (Combat->State == Idle) Action->Execute(EAbilityInput::Action3);
}

void ABody::Action4() const
{
	if (Combat->State == Idle) Action->Execute(EAbilityInput::Action4);
}

int ABody::UpdateMovementDirection()
{
	FRotator rot = GetControlRotation();
	FVector last = GetLastMovementInputVector();
	if (FVector::DotProduct(last, FRotationMatrix(rot).GetScaledAxis(EAxis::X)) > 0.2) MovementDirection = 0;
	else if (FVector::DotProduct(last, FRotationMatrix(rot).GetScaledAxis(EAxis::X)) < -0.2) MovementDirection = 1;
	else if (FVector::DotProduct(last, FRotationMatrix(rot).GetScaledAxis(EAxis::Y)) > 0.2) MovementDirection = 2;
	else if (FVector::DotProduct(last, FRotationMatrix(rot).GetScaledAxis(EAxis::Y)) < -0.2) MovementDirection = 3;
	else MovementDirection = 1;
	return MovementDirection;
}

void ABody::RefreshPitch()
{
	if (Combat->State != Climbing)
	{
		FRotator rot = UKismetMathLibrary::ComposeRotators(GetControlRotation(), FRotator(0, -180, 0));
		Pitch = -rot.Pitch;
	}
	else Pitch = 0;
}

void ABody::SetAttackPressed(bool val)
{
	if (HasAuthority()) AttackPressed = val;
	else ServerSetAttackPressed(val);
}

void ABody::SetBlockPressed(bool val)
{
	if (HasAuthority()) BlockPressed = val;
	else ServerSetBlockPressed(val);
}

void ABody::SetSprintPressed(bool val)
{
	if (HasAuthority()) SprintPressed = val;
	else ServerSetSprintPressed(val);
}

void ABody::PlayMontage(UAnimMontage* nMontage)
{
	if (HasAuthority())
	{
		MultiPlayMontage(nMontage);
		Animator->Montage_Play(nMontage);
		FOnMontageEnded BlendOutDelegate;
		BlendOutDelegate.BindUObject(this, &ABody::OnAnimationBlendOut);
		Animator->Montage_SetBlendingOutDelegate(BlendOutDelegate, nMontage);
	}
	else ServerPlayMontage(nMontage);
}

void ABody::MultiPlayMontage_Implementation(UAnimMontage* nMontage)
{
	Animator->Montage_Play(nMontage);
}

void ABody::OnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted)
{
	if (Combat->State != Dead) Combat->SetState(Idle);
}

void ABody::ShowWorldDamage(int amount, EDamageType nDamageType, FVector hitLocation)
{
	if (HasAuthority()) MultiShowWorldDamage(amount, nDamageType, hitLocation);
	else ServerShowWorldDamage(amount, nDamageType, hitLocation);
}

void ABody::DropTombstone()
{
	if (HasAuthority()) ExecuteDropTombstone();
	else ServerDropTombstone();
}

void ABody::ExecuteDropTombstone()
{
	FVector Location = GetActorLocation();
	Location.Z = Location.Z - Capsule->GetScaledCapsuleHalfHeight();
	FRotator Rotation = GetActorRotation();
	Tombstone = GetWorld()->SpawnActor<ATombstone>(Bitloner->Tombstone.GetDefaultObject()->GetClass(), Location,
	                                               Rotation);
	if (Dropables != nullptr)
	{
		for (auto row : Dropables->GetRowMap())
		{
			FString rowName = (row.Key).ToString();
			FDropable* dropable = (FDropable*)row.Value;
			int rand = FMath::RandRange(0, 100);
			if (dropable->Chance >= rand)
			{
				if (UItem* item = dropable->Item.GetDefaultObject())
				{
					Tombstone->Inventory->Add(item, dropable->Amount);
					GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Dropped " + item->GetName()
					                                 + "x" + FString::FromInt(dropable->Amount));
				}
			}
		}
	}
}

void ABody::ServerShowWorldDamage_Implementation(int amount, EDamageType nDamageType, FVector hitLocation)
{
	MultiShowWorldDamage(amount, nDamageType, hitLocation);
}

void ABody::MultiShowWorldDamage_Implementation(int amount, EDamageType nDamageType, FVector hitLocation)
{
	Info->StartTimer(2);
	OnShowWorldDamage(amount, nDamageType, hitLocation);
}

void ABody::RefreshAttributes()
{
	Attributes->RefreshStats();
	Attributes->Damage = Attributes->BaseDamage;
	Attributes->Defense = Attributes->BaseDefense;
}

void ABody::Die()
{
	Combat->SetState(Dead);
	SetAttackPressed(false);
	if (Npc) Npc->UnPossess();
	SetRagdoll(true);
	GetWorldTimerManager().SetTimer(RespawnHandle, this, &ABody::DestroyCorpse, RespawnTime, false);
	DropTombstone();
}

void ABody::DestroyCorpse()
{
	GetWorldTimerManager().ClearTimer(RespawnHandle);
	if (Respawns) SpawnActor(GetClass(), SpawnPoint, FRotator());
	Destroy();
}

void ABody::FireDamage_Implementation(UXFireInstance* fireInstance, FXFireSettings fireSettings, float maxDamage,
                                      float damage)
{
	IXFireInterface::FireDamage_Implementation(fireInstance, fireSettings, maxDamage, damage);
	TakeDamage(damage, FDamageEvent(URangedDamage::StaticClass()), nullptr, nullptr);
}

bool ABody::OnForceGravityEnabled_Implementation()
{
	GetCharacterMovement()->GravityScale = 1.0;
	return true;
}

bool ABody::OnForceGravityDisabled_Implementation()
{
	GetCharacterMovement()->GravityScale = 0.0;
	return true;
}

bool ABody::IsForceEnabled_Implementation()
{
	return true;
}

UPrimitiveComponent* ABody::GetForceComponent_Implementation()
{
	return GetCapsuleComponent();
}

bool ABody::AddCustomForce_Implementation(UXForceComponent* forceComponent, FVector force)
{
	UCharacterMovementComponent* charMov = GetCharacterMovement();
	charMov->AddForce(charMov->Mass * force);
	return true;
}
