#include "InventoryWidget.h"
#include "EquipmentWidget.h"

void UInventoryWidget::Init(AHero* nHero) const
{
	EquipmentWidget->Init(nHero);
}
