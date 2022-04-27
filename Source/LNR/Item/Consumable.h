#pragma once
#include "CoreMinimal.h"
#include "Item.h"
#include "Consumable.generated.h"

UCLASS(Abstract)
class LNR_API UConsumable : public UItem
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class ABody* Body;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UAnimMontage* Montage;

	virtual void UseItem(AHero* nHero, int amount) override;
	virtual FString PrintItemData(bool withDescription) override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Consume(ABody* nBody);
	virtual void Consume_Implementation(ABody* nBody);
	
	UFUNCTION(BlueprintCallable)
	void UseConsumable(ABody* nBody);
	UFUNCTION(Server, Reliable)
	void ServerUseConsumable(ABody* nBody);
	void ServerUseConsumable_Implementation(ABody* nBody) { UseConsumable(nBody); }

	UFUNCTION(BlueprintCallable)
	void PlayMontage(ABody* nBody, UAnimMontage* nMontage);
	void OnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted);
	UFUNCTION()
	void OnNotifyBegin(FName nName, const FBranchingPointNotifyPayload& payload);

	
};
