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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSlotClicked);

	UPROPERTY(BlueprintAssignable)
	FSlotClicked OnClick;

	virtual void NativeConstruct() override;
	void Setup(UTexture2D* icon) const;
	UFUNCTION(BlueprintCallable)
	virtual void Click();
};
