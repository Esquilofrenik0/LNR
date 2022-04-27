#pragma once
#include "Consumable.h"
#include "Gadget.generated.h"

UCLASS(Abstract)
class LNR_API UGadget : public UConsumable
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AGadgetBase> Gadget;
	virtual void Consume_Implementation(ABody* nBody) override;
};
