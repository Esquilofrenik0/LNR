#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MorphSliderWidget.generated.h"

UCLASS(Abstract)
class LNR_API UMorphSliderWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FName MorphName;
	UPROPERTY(BlueprintReadWrite)
	class AAvatar* Avatar;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* Morph;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlider* Slider;
	void Init(AAvatar* nAvatar, FName nMorphName);
	void SliderChanged(float val);
};
