#include "SlotCraftWidget.h"
#include "LNR/Body/Hero.h"

void USlotCraftWidget::Init(AHero* nHero)
{
	Hero = nHero;
}

void USlotCraftWidget::Click()
{
	// if (Hero->Container->Slots[SlotNumber].Item != nullptr)
	// {
		// Hero->Inventory->Store(Hero->Container, Hero->Container->Slots[SlotNumber].Item,
		                       // Hero->Container->Slots[SlotNumber].Amount);
	// }
}
