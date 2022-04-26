#include "HudWidget.h"
#include "ActionBarWidget.h"
#include "AttributesWidget.h"
#include "Blueprint/WidgetTree.h"
#include "LNR/Body/Hero.h"

void UHudWidget::Init(AHudBitloner* nHud)
{
	Hud = nHud;
	ShowInteractionIcon(false);
	ActionBarWidget->Init(Hud->Hero->Action);
	AttributesWidget->Init(Hud->Hero->Attributes);
}

void UHudWidget::ShowInteractionIcon(bool val)
{
	if (val) InteractionImage->SetVisibility(ESlateVisibility::Visible);
	else InteractionImage->SetVisibility(ESlateVisibility::Hidden);
}
