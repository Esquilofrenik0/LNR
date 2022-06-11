#include "InventoryWidget.h"
#include "BagWidget.h"
#include "ContainerWidget.h"
#include "CraftWidget.h"
#include "EquipmentWidget.h"
#include "LNR/Body/Hero.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryWidget::Init(AHero* nHero) const
{
	BagWidget->Init(nHero);
	CraftWidget->Init(nHero);
	ContainerWidget->Init(nHero);
	EquipmentWidget->Init(nHero);
}
