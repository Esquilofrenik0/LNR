#pragma once
#include "CoreMinimal.h"
#include "LNR/LNR.h"
#include "Engine/StaticMeshActor.h"
#include "GadgetBase.generated.h"

UCLASS(Abstract, Blueprintable)
class LNR_API AGadgetBase : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AGadgetBase();
	UFUNCTION(BlueprintNativeEvent)
	void ActivateGadget(class ABody* body, FVector location);
	virtual void ActivateGadget_Implementation(class ABody* body, FVector location);
};
