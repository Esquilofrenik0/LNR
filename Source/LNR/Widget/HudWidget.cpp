#include "HudWidget.h"
#include "ActionBarWidget.h"
#include "AttributesWidget.h"
#include "InventoryWidget.h"

void UHudWidget::Init(AHudBitloner* nHud)
{
	Hud = nHud;
	ActionBarWidget->Init(Hud->Hero);
	AttributesWidget->Init(Hud->Hero);
	InventoryWidget->Init(Hud->Hero);
}
