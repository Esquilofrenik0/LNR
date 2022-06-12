#pragma once
#include "CoreMinimal.h"
#include "LNR/Component/MarkerComponent.h"
#include "UObject/Interface.h"
#include "Marked.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class UMarked : public UInterface
{
	GENERATED_BODY()
};

class LNR_API IMarked
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UMarkerComponent* GetMarker();
};
