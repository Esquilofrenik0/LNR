#include "MorphPageWidget.h"
#include "MorphSliderWidget.h"
#include "Components/VerticalBox.h"

void UMorphPageWidget::Init(AAvatar* nAvatar)
{
	Avatar = nAvatar;
	for (int i = 0; i < MorphPageData.MorphNames.Num(); i++)
	{
		UWidget* widget = CreateWidget(this, MorphSliderTemplate);
		Box->AddChildToVerticalBox(widget);
		UMorphSliderWidget* morphSlider = Cast<UMorphSliderWidget>(widget);
		morphSlider->Init(Avatar, MorphPageData.MorphNames[i]);
	}
}
