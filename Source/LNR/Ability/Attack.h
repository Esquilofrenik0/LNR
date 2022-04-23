#pragma once
#include "CoreMinimal.h"
#include "LNR/Ability/Ability.h"
#include "Attack.generated.h"

UCLASS()
class LNR_API UAttack : public UAbility
{
	GENERATED_BODY()
public:
	UAttack();

	UPROPERTY(BlueprintReadWrite)
	class ABody* Body;
	UPROPERTY(BlueprintReadWrite)
	class AHero* Hero;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                        const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
	                        bool bWasCancelled) override;
	virtual void PreAttack(ABody* nBody);
	UFUNCTION(NetMulticast, Reliable)
	void MultiPlayMontage(USkeletalMeshComponent* Mesh, UAnimMontage* montage);
	void OnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted);
};
