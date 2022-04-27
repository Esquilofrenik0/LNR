#pragma once
#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LNR/Ability/Ability.h"
#include "Reload.generated.h"

UCLASS()
class LNR_API UReload : public UAbility
{
	GENERATED_BODY()
public:
	UReload();
	UPROPERTY(BlueprintReadWrite)
	class AHumanoid* Humanoid;
	UPROPERTY(BlueprintReadWrite)
	class AHero* Hero;
	UPROPERTY(BlueprintReadWrite)
	class UGun* Gun;
	UPROPERTY(BlueprintReadWrite)
	class UCharacterMovementComponent* Move;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(NetMulticast, Reliable)
	void MultiPlayMontage(USkeletalMeshComponent* Mesh, UAnimMontage* montage);
	void OnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted);

	UFUNCTION(Client, Reliable)
	void ClientSetSpeed(float Speed, class UCharacterMovementComponent* CharacterMovement);
};
