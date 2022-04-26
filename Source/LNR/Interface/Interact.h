#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interact.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class UInteract : public UInterface
{
	GENERATED_BODY()
};

class LNR_API IInteract
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnInteract(class AHero* hero);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnShowInfo(class AHero* hero, bool val);
};
