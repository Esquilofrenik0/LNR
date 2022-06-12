#include "CraftWidget.h"
#include "SlotCraftWidget.h"
#include "Blueprint/WidgetTree.h"
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
}

void UCraftWidget::Refresh()
{
	for (int i = 0; i < Hero->Crafting->Book.Num(); i++)
	{
		if (i >= Slots.Num())
		{
			UWidget* widget = CreateWidget(this, SlotTemplate);
			SlotBox->AddChild(widget);
			USlotCraftWidget* slot = Cast<USlotCraftWidget>(widget);
			slot->SlotNumber = i;
			slot->Init(Hero);
			Slots.Add(slot);
		}
		Slots[i]->SetIsEnabled(true);
		Slots[i]->Setup(Hero->Crafting->Book[i].GetDefaultObject()->Icon, 1);
	}
	TArray<int> toRemove;
	for (int i = 0; i < Slots.Num(); i++)
	{
		if (i >= Hero->Crafting->Book.Num()) toRemove.Add(i);
	}
	for (int i = 0; i < toRemove.Num(); i++)
	{
		Slots[i]->Destruct();
		Slots.RemoveAt(i);
	}
}
