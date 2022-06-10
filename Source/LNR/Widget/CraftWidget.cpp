#include "CraftWidget.h"
#include "SlotCraftWidget.h"
#include "Components/WrapBox.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/CraftingComponent.h"
#include "LNR/Item/Recipe.h"

void UCraftWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void UCraftWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	Refresh();
}

void UCraftWidget::Init(AHero* nHero)
{
	Hero = nHero;
	Slots.Empty();
	SlotBox->ClearChildren();
	for (int i = 0; i < Hero->Crafting->Book.Num(); i++)
	{
		USlotCraftWidget* slot = NewObject<USlotCraftWidget>();
		slot->SlotNumber = i;
		slot->Init(Hero);
		Slots.Add(slot);
	}
}

void UCraftWidget::Refresh() const
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		Slots[i]->SetIsEnabled(true);
		Slots[i]->Setup(Hero->Crafting->Book[i].GetDefaultObject()->Icon, 1);
	}
}
