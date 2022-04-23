#pragma once
#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LNR/Ability/Ability.h"
#include "Sprint.generated.h"

UCLASS()
class LNR_API USprint : public UAbility
{
	GENERATED_BODY()
public:
	USprint();

	UPROPERTY()
	class ABody* Body;
	UPROPERTY()
	class UCharacterMovementComponent* Move;
	UPROPERTY()
	FTimerHandle SprintTimer;

	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	void TickSprint();
	UFUNCTION(Client, Reliable)
	void ClientSetSpeed(float Speed, class UCharacterMovementComponent* CharacterMovement);
};
