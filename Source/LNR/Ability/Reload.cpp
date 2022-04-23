#include "Reload.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "LNR/Body/Body.h"
#include "LNR/Body/Human.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/CombatComponent.h"
#include "LNR/Item/Gun.h"
#include "LNR/Component/EquipmentComponent.h"

UReload::UReload()
{
	AbilityInput = EAbilityInput::Reload;
}

void UReload::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                              const FGameplayAbilityActivationInfo ActivationInfo,
                              const FGameplayEventData* TriggerEventData)
{
	Print("Reload Activated!");
	if (ABody* body = Cast<ABody>(ActorInfo->AvatarActor))
	{
		Body = body;
		// if (AHero* hero = Cast<AHero>(body))
		// {
		// 	Hero = hero;
		// 	if (Hero->Equipment->AmmoSlot.Amount < 1) return;
		// }
		if (UGun* gun = Cast<UGun>(body->Equipment->GetWeapon(0)))
		{
			Gun = gun;
			// if (Human->Equipment->AmmoSlot.Loaded >= Gun->MaxAmmo) return;
			// UAnimMontage* MontageToPlay = Gun->ReloadMontage;
			// Human->State = Reacting;
			// Move = Human->GetCharacterMovement();
			// Move->MaxWalkSpeed = Human->WalkSpeed;
			// ClientSetSpeed(Human->WalkSpeed, Move);
			// USkeletalMeshComponent* Mesh = Human->GetMesh();
			// MultiPlayMontage(Mesh, MontageToPlay);
			// UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
			// AnimInstance->Montage_Play(MontageToPlay);
			// FOnMontageEnded BlendOutDelegate;
			// BlendOutDelegate.BindUObject(this, &UReload::OnAnimationBlendOut);
			// AnimInstance->Montage_SetBlendingOutDelegate(BlendOutDelegate, MontageToPlay);
		}
	}
}

void UReload::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                         const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                         bool bWasCancelled)
{
	if (Body)
	{
		if (Move)
		{
			Move->MaxWalkSpeed = Body->RunSpeed;
			ClientSetSpeed(Body->RunSpeed, Move);
		}
		Body->Combat->State = Idle;
		if (Body->BlockPressed) Body->Block();
		else if (Body->AttackPressed) Body->Attack();
	}
}

void UReload::MultiPlayMontage_Implementation(USkeletalMeshComponent* Mesh, UAnimMontage* montage)
{
	Mesh->GetAnimInstance()->Montage_Play(montage);
}

void UReload::OnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted)
{
	// if (!bInterrupted)
	// {
		// if (Hero)
		// {
			// int missingAmount = Gun->MaxAmmo - Hero->Equipment->AmmoSlot.Loaded;
			// if (Hero->Equipment->AmmoSlot.Amount >= missingAmount)
			// {
			// 	Hero->Equipment->AmmoSlot.Loaded += missingAmount;
			// 	Hero->Equipment->AmmoSlot.Amount -= missingAmount;
			// }
			// else
			// {
			// 	Hero->Equipment->AmmoSlot.Loaded += Hero->Equipment->AmmoSlot.Amount;
			// 	Hero->Equipment->AmmoSlot.Amount = 0;
			// }
		// }
		// else Human->Equipment->AmmoSlot.Loaded = Gun->MaxAmmo;
	// }
	K2_EndAbility();
}

void UReload::ClientSetSpeed_Implementation(float Speed, UCharacterMovementComponent* CharacterMovement)
{
	CharacterMovement->MaxWalkSpeed = Speed;
}
