#include "HudWidget.h"
#include "ActionBarWidget.h"
#include "AttributesWidget.h"
#include "InventoryWidget.h"
#include "LNR/Body/Hero.h"

void UHudWidget::Init(AHudBitloner* nHud)
{
	Hud = nHud;
	ActionBarWidget->Init(Hud->Hero->Action);
	AttributesWidget->Init(Hud->Hero->Attributes);
	InventoryWidget->Init(Hud->Hero);
}
