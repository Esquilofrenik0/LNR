#include "SlotContainerWidget.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/InventoryComponent.h"

void USlotContainerWidget::Init(AHero* nHero)
{
	Hero = nHero;
}

void USlotContainerWidget::Click()
{
	if (Hero->Container->Slots[SlotNumber].Item != nullptr)
	{
		Hero->Inventory->Store(Hero->Container, Hero->Container->Slots[SlotNumber].Item,
		                       Hero->Container->Slots[SlotNumber].Amount);
	}
}
