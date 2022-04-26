#include "InventoryWidget.h"
#include "BagWidget.h"
#include "EquipmentWidget.h"
#include "LNR/Body/Hero.h"

void UInventoryWidget::Init(AHero* nHero) const
{
	BagWidget->Init(nHero);
	EquipmentWidget->Init(nHero);
}
