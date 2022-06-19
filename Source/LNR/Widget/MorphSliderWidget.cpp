#include "MorphSliderWidget.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "LNR/Body/Avatar.h"

void UMorphSliderWidget::Init(AAvatar* nAvatar, FName nMorphName)
{
	Avatar = nAvatar;
	MorphName = nMorphName;
	Morph->SetText(FText::FromName(MorphName));
	Slider->OnValueChanged.AddDynamic(this, &UMorphSliderWidget::SliderChanged);
}

void UMorphSliderWidget::SliderChanged(float val)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Morph Slider Value Changed!");
	Avatar->GetMesh()->SetMorphTarget(MorphName, val);
}
