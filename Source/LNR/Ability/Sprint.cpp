#include "Sprint.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "LNR/Body/Body.h"
#include "LNR/Component/AttributesComponent.h"
#include "LNR/Component/CombatComponent.h"

USprint::USprint()
{
	AbilityInput = EAbilityInput::Sprint;
}

void USprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                              const FGameplayAbilityActivationInfo ActivationInfo,
                              const FGameplayEventData* TriggerEventData)
{
	if (ABody* body = Cast<ABody>(ActorInfo->AvatarActor))
	{
		Body = body;
		Move = Body->GetCharacterMovement();
		Move->MaxWalkSpeed = Body->SprintSpeed;
		ClientSetSpeed(Body->SprintSpeed, Move);
		Body->GetWorldTimerManager().ClearTimer(SprintTimer);
		Body->GetWorldTimerManager().SetTimer(SprintTimer, this, &USprint::TickSprint, 0.1, true);
	}
}

void USprint::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                         const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                         bool bWasCancelled)
{
	Body->GetWorldTimerManager().ClearTimer(SprintTimer);
	if (Body->Combat->State == Idle)
	{
		Move->MaxWalkSpeed = Body->RunSpeed;
		ClientSetSpeed(Body->RunSpeed, Move);
	}
}

void USprint::TickSprint()
{
	if (Body->SprintPressed && Body->Combat->State == Idle) Body->Attributes->Stamina -= 1;
	else K2_EndAbility();
}

void USprint::ClientSetSpeed_Implementation(float Speed, UCharacterMovementComponent* CharacterMovement)
{
	CharacterMovement->MaxWalkSpeed = Speed;
}
