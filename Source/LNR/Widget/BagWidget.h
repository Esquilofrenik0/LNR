#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BagWidget.generated.h"

UCLASS()
class LNR_API UBagWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* LabelText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UWrapBox* SlotBox;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* InfoText;
	UPROPERTY(BlueprintReadWrite)
	TArray<class USlotWidget*> Slots;
	virtual void NativeConstruct() override;
	void Refresh(class UInventoryComponent* inventory) const;
};
