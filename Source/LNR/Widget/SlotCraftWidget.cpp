#include "SlotCraftWidget.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/CraftingComponent.h"
#include "LNR/Component/InventoryComponent.h"
#include "LNR/Game/Playor.h"
#include "LNR/Item/Recipe.h"

void USlotCraftWidget::Init(AHero* nHero)
{
	Hero = nHero;
}

void USlotCraftWidget::Click()
{
	if (URecipe* rec = Hero->Crafting->Book[SlotNumber].GetDefaultObject())
	{
		for (int i = 0; i < rec->Cost.Num(); i++)
		{
			if (!Hero->Inventory->Contains(rec->Cost[i].Item.GetDefaultObject(), rec->Cost[i].Amount))
			{
				Hero->Player->Print("Not enough resources!");
				return;
			}
		}
		for (int i = 0; i < rec->Cost.Num(); i++)
		{
			Hero->Inventory->Remove(rec->Cost[i].Item.GetDefaultObject(), rec->Cost[i].Amount);
			Hero->Inventory->Add(rec->Result.Item.GetDefaultObject(), rec->Result.Amount);
			Hero->Player->Print("Crafting Success!");
		}
	}
}
