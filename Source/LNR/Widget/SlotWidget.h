#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotWidget.generated.h"

UCLASS()
class LNR_API USlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UImage* Image;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UButton* Button;
};
