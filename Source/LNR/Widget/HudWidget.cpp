#include "HudWidget.h"
#include "AttributesWidget.h"
#include "Blueprint/WidgetTree.h"
#include "LNR/Body/Hero.h"

void UHudWidget::Init(AHudBitloner* nHud)
{
	Hud = nHud;
	AttributesWidget->Attributes = Hud->Hero->Attributes;
	ShowInteractionIcon(false);
}

void UHudWidget::ShowInteractionIcon(bool val)
{
	if (val) InteractionImage->SetVisibility(ESlateVisibility::Visible);
	else InteractionImage->SetVisibility(ESlateVisibility::Hidden);
}
