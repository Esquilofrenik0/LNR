#include "Attack.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "LNR/Body/Body.h"
#include "LNR/Body/Human.h"
#include "LNR/Item/Gun.h"
#include "LNR/Component/CombatComponent.h"
#include "LNR/Component/EquipmentComponent.h"

UAttack::UAttack()
{
	AbilityInput = EAbilityInput::Attack;
}

void UAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                              const FGameplayAbilityActivationInfo ActivationInfo,
                              const FGameplayEventData* TriggerEventData)
{
	if (ABody* body = Cast<ABody>(ActorInfo->AvatarActor))
	{
		PreAttack(body);
		if (Humanoid)
		{
			if (Humanoid->Equipment->Holster) Humanoid->Equipment->SetHolster(false);
			if (Cast<UGun>(Humanoid->Equipment->Weapon[0]))
			{
				if (Humanoid->Equipment->AmmoSlot.Loaded < 1)
				{
					Body->Combat->State = Idle;
					Body->Reload();
					return;
				}
				else
				{
					// Humanoid->IsShooting = true;
					Humanoid->Equipment->AmmoSlot.Loaded -= 1;
					Humanoid->Combat->Shoot();
				}
			}
		}
		Body->Combat->MeleeHits.Empty();
		GetWorld()->GetTimerManager().ClearTimer(Body->Combat->ResetComboHandle);
		Body->Combat->Combo %= Body->Combat->GetMaxCombo();
		Body->Combat->SetState(Attacking);
		USkeletalMeshComponent* Mesh = Body->GetMesh();
		UAnimMontage* MontageToPlay = Body->Combat->GetCombatMontage();
		MultiPlayMontage(Mesh, MontageToPlay);
		UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
		AnimInstance->Montage_Play(MontageToPlay);
		FOnMontageEnded BlendOutDelegate;
		BlendOutDelegate.BindUObject(this, &UAttack::OnAnimationBlendOut);
		AnimInstance->Montage_SetBlendingOutDelegate(BlendOutDelegate, MontageToPlay);
		Body->Combat->Combo += 1;
		Body->Combat->Combo %= Body->Combat->GetMaxCombo();
	}
}

void UAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                         const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                         bool bWasCancelled)
{
	// if (Human) Human->IsShooting = false;
	if (!bWasCancelled)
	{
		Body->Combat->SetState(Idle);
		if (Body->AttackPressed) Body->Attack();
		else if (Body->BlockPressed) Body->Block();
	}
}

void UAttack::PreAttack(ABody* nBody)
{
	Body = nBody;
	Humanoid = Cast<AHuman>(Body);
}

void UAttack::MultiPlayMontage_Implementation(USkeletalMeshComponent* Mesh, UAnimMontage* montage)
{
	Mesh->GetAnimInstance()->Montage_Play(montage);
}

void UAttack::OnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted)
{
	GetWorld()->GetTimerManager().SetTimer(Body->Combat->ResetComboHandle, Body->Combat,
	                                       &UCombatComponent::ResetCombo, 2.0f, false);
	if (bInterrupted) K2_CancelAbility();
	else K2_EndAbility();
}
