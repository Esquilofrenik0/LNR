#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BagWidget.generated.h"

UCLASS()
class LNR_API UBagWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class AHero* Hero;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* LabelText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UWrapBox* SlotBox;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* InfoText;
	UPROPERTY(BlueprintReadWrite)
	TArray<class USlotInventoryWidget*> Slots;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void Init(AHero* nHero);
	void Refresh() const;
};
