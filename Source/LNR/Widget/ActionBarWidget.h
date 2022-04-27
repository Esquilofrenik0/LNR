#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionBarWidget.generated.h"

UCLASS()
class LNR_API UActionBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class AHero* Hero;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* Action1Slot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* Action2Slot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* Action3Slot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* Action4Slot;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void Init(AHero* nHero);
	void Refresh() const;
};
