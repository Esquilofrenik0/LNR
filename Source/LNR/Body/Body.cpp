#include "Body.h"
#include "NavigationInvokerComponent.h"
#include "LNR/LNR.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LNR/AI/Npc.h"
#include "LNR/Component/ActionComponent.h"
#include "LNR/Component/AttributesComponent.h"
#include "LNR/Component/CombatComponent.h"
#include "LNR/Component/EquipmentComponent.h"
#include "LNR/DamageType/MeleeDamage.h"
#include "LNR/Component/InfoComponent.h"
#include "Net/UnrealNetwork.h"

ABody::ABody()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(35.f, 85.0f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->GravityScale = 1.75f;

	NavigationInvoker = CreateDefaultSubobject<UNavigationInvokerComponent>("Navigation Invoker");
	Info = CreateDefaultSubobject<UInfoComponent>("Info");
	Info->Setup(this);
	Action = CreateDefaultSubobject<UActionComponent>("Action");
	Action->SetIsReplicated(true);
	Action->SetReplicationMode(EGameplayEffectReplicationMode::Full);
	Attributes = CreateDefaultSubobject<UAttributesComponent>("Attributes");
	Combat = CreateDefaultSubobject<UCombatComponent>("Combat");
	Combat->Setup(this);
	Equipment = CreateDefaultSubobject<UEquipmentComponent>("Equipment");
	Equipment->Setup(this);
}

void ABody::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABody, Pitch);
	DOREPLIFETIME(ABody, MovementDirection);
	DOREPLIFETIME_CONDITION_NOTIFY(ABody, AttackPressed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABody, BlockPressed, COND_None, REPNOTIFY_Always);
}

void ABody::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ABody::BeginPlay()
{
	Super::BeginPlay();
	Npc = Cast<ANpc>(GetController());
	RefreshAttributes();
	Info->Init(Attributes);
}

void ABody::Restart()
{
	Super::Restart();
	Action->InitAbilityActorInfo(this, this);
	if (HasAuthority()) Action->InitializeAbilities();
}

float ABody::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                        AActor* DamageCauser)
{
	if (Combat->State == Dead) return 0;
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ABody* instigator = Cast<ABody>(DamageCauser);
	// if (Npc)
	// {
	// 	if(Npc->Target == nullptr) Npc->TryTarget(instigator);
	// 	Npc->StartUnderAttack();
	// }
	// if (IsCitizen && instigator && !instigator->IsCitizen) instigator->Attributes->ChangeHate(2);
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
			if (instigator)
			{
				instigator->Combat->SetState(Reacting);
				instigator->PlayMontage(instigator->GetMesh(), instigator->Combat->TakeDamageMontage);
				Combat->ResetCombo();
			}
		}
		else
		{
			Combat->SetState(Reacting);
			PlayMontage(GetMesh(), Combat->TakeDamageMontage);
			Combat->ResetCombo();
		}
	}
	Attributes->ChangeHealth(-DamageAmount);
	ShowWorldDamage(DamageAmount, dt, GetActorLocation());
	// if (Attributes->Health <= 0) Die();
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

void ABody::PlayMontage(USkeletalMeshComponent* nMesh, UAnimMontage* nMontage)
{
	if (HasAuthority())
	{
		MultiPlayMontage(nMesh, nMontage);
		UAnimInstance* AnimInstance = nMesh->GetAnimInstance();
		AnimInstance->Montage_Play(nMontage);
		FOnMontageEnded BlendOutDelegate;
		BlendOutDelegate.BindUObject(this, &ABody::OnAnimationBlendOut);
		AnimInstance->Montage_SetBlendingOutDelegate(BlendOutDelegate, nMontage);
	}
	else ServerPlayMontage(nMesh, nMontage);
}

void ABody::ServerPlayMontage_Implementation(USkeletalMeshComponent* nMesh, UAnimMontage* nMontage)
{
	PlayMontage(nMesh, nMontage);
}

void ABody::MultiPlayMontage_Implementation(USkeletalMeshComponent* nMesh, UAnimMontage* nMontage)
{
	nMesh->GetAnimInstance()->Montage_Play(nMontage);
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

void ABody::ServerShowWorldDamage_Implementation(int amount, EDamageType nDamageType, FVector hitLocation)
{
	MultiShowWorldDamage(amount, nDamageType, hitLocation);
}

void ABody::MultiShowWorldDamage_Implementation(int amount, EDamageType nDamageType, FVector hitLocation)
{
	Info->StartTimer(2);
	OnShowWorldDamage(amount, nDamageType, hitLocation);
}

void ABody::OnInteract_Implementation(AHero* hero)
{
}

void ABody::OnShowInfo_Implementation(AHero* hero, bool val)
{
	Info->Show(val);
}

void ABody::RefreshAttributes()
{
	Attributes->RefreshStats();
	Attributes->Damage = Attributes->BaseDamage;
	Attributes->Defense = Attributes->BaseDefense;
	if (UWeapon* mw = Equipment->GetWeapon(0))
	{
		Attributes->Damage += mw->Damage;
		Attributes->Defense += mw->Defense;
	}
	if (UWeapon* ow = Equipment->GetWeapon(1))
	{
		Attributes->Damage += ow->Damage;
		Attributes->Defense += ow->Defense;
	}
}
