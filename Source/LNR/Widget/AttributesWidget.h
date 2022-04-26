#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributesWidget.generated.h"

UCLASS()
class LNR_API UAttributesWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class UAttributesComponent* Attributes;
};
