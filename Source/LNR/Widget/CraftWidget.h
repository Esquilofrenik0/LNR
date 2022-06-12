#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CraftWidget.generated.h"

UCLASS(Abstract)
class LNR_API UCraftWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class USlotCraftWidget> SlotTemplate;
	UPROPERTY(BlueprintReadWrite)
	class AHero* Hero;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* LabelText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UWrapBox* SlotBox;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* InfoText;
	UPROPERTY(BlueprintReadWrite)
	TArray<USlotCraftWidget*> Slots;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void Init(AHero* nHero);
	void Refresh();
};
