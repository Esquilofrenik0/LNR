#pragma once
#include "CoreMinimal.h"
#include "Consumable.h"
// #include "LNR/World/Gadget/GadgetBase.h"
#include "Gadget.generated.h"

UCLASS(Abstract)
class LNR_API UGadget : public UConsumable
{
	GENERATED_BODY()
public:
	// UPROPERTY(BlueprintReadWrite, EditAnywhere)
	// class TSubclassOf<AGadgetBase> Gadget;
	virtual void Consume_Implementation(ABody* nBody) override;
};
