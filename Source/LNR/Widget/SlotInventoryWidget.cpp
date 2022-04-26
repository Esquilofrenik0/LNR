#include "SlotInventoryWidget.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/InventoryComponent.h"

void USlotInventoryWidget::Init(AHero* nHero)
{
	Hero = nHero;
}

void USlotInventoryWidget::Click()
{
	if (Hero->Inventory->Slots[SlotNumber].Item != nullptr) Hero->Inventory->Slots[SlotNumber].Item->UseItem(Hero, 1);
}
