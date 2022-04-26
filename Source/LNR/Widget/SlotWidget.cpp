#include "SlotWidget.h"
#include "Components/Image.h"

void USlotWidget::Setup(UTexture2D* icon)
{
	if (icon != nullptr)
	{
		Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		Image->SetBrushFromTexture(icon);
	}
	else Image->SetVisibility(ESlateVisibility::Hidden);
}
