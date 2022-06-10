#include "SlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic(this, &USlotWidget::Click);
}

void USlotWidget::Setup(UTexture2D* icon, int amount) const
{
	if (icon != nullptr)
	{
		Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		Image->SetBrushFromTexture(icon);
		if (amount > 1)
		{
			Amount->SetText(FText::AsNumber(amount));
			Amount->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
		else Amount->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Amount->SetVisibility(ESlateVisibility::Hidden);
		Image->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USlotWidget::Click()
{
	OnClick.Broadcast();
}
