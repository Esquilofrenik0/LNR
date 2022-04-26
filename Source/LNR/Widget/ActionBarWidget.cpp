#include "ActionBarWidget.h"
#include "SlotWidget.h"
#include "Components/Image.h"
#include "LNR/Component/ActionComponent.h"

void UActionBarWidget::Init(UActionComponent* nAction)
{
	Action = nAction;
	Refresh();
}

void UActionBarWidget::Refresh() const
{
	if (Action->ActionBar[0] != nullptr)
	{
		Action1Slot->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		Action1Slot->Image->SetBrushFromTexture(Action->ActionBar[0].GetDefaultObject()->Icon);
	}
	else Action1Slot->Image->SetVisibility(ESlateVisibility::Hidden);
	if (Action->ActionBar[1] != nullptr)
	{
		Action2Slot->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		Action2Slot->Image->SetBrushFromTexture(Action->ActionBar[1].GetDefaultObject()->Icon);
	}
	else Action2Slot->Image->SetVisibility(ESlateVisibility::Hidden);
	if (Action->ActionBar[2] != nullptr)
	{
		Action3Slot->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		Action3Slot->Image->SetBrushFromTexture(Action->ActionBar[2].GetDefaultObject()->Icon);
	}
	else Action3Slot->Image->SetVisibility(ESlateVisibility::Hidden);
	if (Action->ActionBar[3] != nullptr)
	{
		Action4Slot->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		Action4Slot->Image->SetBrushFromTexture(Action->ActionBar[3].GetDefaultObject()->Icon);
	}
	else Action4Slot->Image->SetVisibility(ESlateVisibility::Hidden);
}
