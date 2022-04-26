#include "SlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"

void USlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &USlotWidget::Click);
}

void USlotWidget::Setup(UTexture2D* icon) const
{
	if (icon != nullptr)
	{
		Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		Image->SetBrushFromTexture(icon);
	}
	else Image->SetVisibility(ESlateVisibility::Hidden);
}

void USlotWidget::Click()
{
	OnClick.Broadcast();
}
