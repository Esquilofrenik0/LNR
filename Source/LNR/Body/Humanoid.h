#pragma once

#include "CoreMinimal.h"
#include "Body.h"
#include "Humanoid.generated.h"

UCLASS()
class LNR_API AHumanoid : public ABody
{
	GENERATED_BODY()
public:
	AHumanoid();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UEquipmentComponent* Equipment;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void RefreshAttributes() override;

	UFUNCTION(BlueprintCallable)
	void ActivateConsumable(int index);
	UFUNCTION(Server, Reliable)
	void ServerActivateConsumable(int index);
	void ServerActivateConsumable_Implementation(int index) { ActivateConsumable(index); }
};
