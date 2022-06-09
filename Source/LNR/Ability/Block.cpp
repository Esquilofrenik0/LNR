#include "Block.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Camera/CameraComponent.h"
#include "LNR/Body/Body.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/CombatComponent.h"
#include "LNR/Component/EquipmentComponent.h"
#include "LNR/Component/WeaponComponent.h"
#include "LNR/Item/Gun.h"
#include "LNR/Item/Shield.h"

UBlock::UBlock()
{
	AbilityInput = EAbilityInput::Block;
}

void UBlock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                             const FGameplayAbilityActivationInfo ActivationInfo,
                             const FGameplayEventData* TriggerEventData)
{
	if (ABody* body = Cast<ABody>(ActorInfo->AvatarActor))
	{
		Body = body;
		Humanoid = Cast<AHumanoid>(Body);
		if (Humanoid)
		{
			if (Humanoid->Equipment->Holster) Humanoid->Equipment->SetHolster(false);
			if (Humanoid->Equipment->LeftHand) Humanoid->Equipment->LeftHand->SetRelativeScale3D(FVector(3, 3, 3));
		}
		Hero = Cast<AHero>(Body);
		// if (Hero && Cast<UGun>(Hero->Equipment->Weapon[0]) && !Cast<UShield>(Hero->Equipment->Weapon[1]))
		// {
			// Hero->EnterAim();
		// }
		Move = Body->GetCharacterMovement();
		Move->MaxWalkSpeed = Body->WalkSpeed;
		ClientSetSpeed(Body->WalkSpeed, Move);
		Body->Combat->SetState(Blocking);
		Body->GetWorldTimerManager().ClearTimer(BlockTimer);
		Body->GetWorldTimerManager().SetTimer(BlockTimer, this, &UBlock::TickBlock, 0.1, true);
	}
}

void UBlock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                        bool bWasCancelled)
{
	Body->GetWorldTimerManager().ClearTimer(BlockTimer);
	Move->MaxWalkSpeed = Body->RunSpeed;
	ClientSetSpeed(Body->RunSpeed, Move);
	Body->Combat->SetState(Idle);
	if (Humanoid && Humanoid->Equipment->LeftHand) Humanoid->Equipment->LeftHand->SetRelativeScale3D(FVector(1, 1, 1));
	// if (Hero) Hero->ExitAim();
}

void UBlock::TickBlock()
{
	if (!Body->BlockPressed) K2_EndAbility();
}

void UBlock::ClientSetSpeed_Implementation(float Speed, UCharacterMovementComponent* CharacterMovement)
{
	CharacterMovement->MaxWalkSpeed = Speed;
}

void UBlock::ClientSetCamera_Implementation(AHero* nHero, bool reset)
{
	if (reset) nHero->TpCamera->FieldOfView = 90;
	else nHero->TpCamera->FieldOfView = 30;
}
