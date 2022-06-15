#include "HudWidget.h"
#include "ActionBarWidget.h"
#include "AttributesWidget.h"
#include "CompassWidget.h"
#include "InventoryWidget.h"
#include "WorldMapWidget.h"

void UHudWidget::Init(AHudBitloner* nHud)
{
	Hud = nHud;
	ActionBarWidget->Init(Hud->Hero);
	AttributesWidget->Init(Hud->Hero);
	CompassWidget->Init(Hud->Hero);
	WorldMapWidget->Init(Hud->Hero);
	InventoryWidget->Init(Hud->Hero);
	WarningText->SetVisibility(ESlateVisibility::Hidden);
	WorldMapWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UHudWidget::Print(FString txt)
{
	WarningText->SetVisibility(ESlateVisibility::HitTestInvisible);
	const FText setTxt = FText::FromString(WarningText->Text.ToString() + txt + "\r");
	WarningText->SetText(setTxt);
	GetWorld()->GetTimerManager().ClearTimer(PrintHandle);
	GetWorld()->GetTimerManager().SetTimer(PrintHandle, this, &UHudWidget::ClearPrint, 4);
}

void UHudWidget::ClearPrint()
{
	GetWorld()->GetTimerManager().ClearTimer(PrintHandle);
	WarningText->SetText(FText::FromString(""));
	WarningText->SetVisibility(ESlateVisibility::Hidden);
}
