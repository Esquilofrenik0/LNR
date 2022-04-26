#include "InventoryComponent.h"

UInventoryComponent::UInventoryComponent()
{
	Slots.Init(FSlot(), 64);
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
}

bool UInventoryComponent::Add(UItem* item, int amount)
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		if (Slots[i].Item != nullptr)
		{
			if (Slots[i].Item == item && Slots[i].Amount < Slots[i].Item->Stack)
			{
				if (Slots[i].Amount + amount > Slots[i].Item->Stack)
				{
					const int missing = Slots[i].Item->Stack - Slots[i].Amount;
					Slots[i].Amount += missing;
					amount -= missing;
				}
				else
				{
					Slots[i].Amount += amount;
					return true;
				}
			}
		}
	}
	for (int i = 0; i < Slots.Num(); i++)
	{
		if (Slots[i].Item == nullptr)
		{
			Slots[i].Item = item;
			Slots[i].Amount = amount;
			return true;
		}
	}
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Inventory full!");
	return false;
}

bool UInventoryComponent::Remove(UItem* item, int amount)
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		if (Slots[i].Item != nullptr)
		{
			if (Slots[i].Item == item && Slots[i].Amount >= amount)
			{
				Slots[i].Amount -= amount;
				if (Slots[i].Amount <= 0) Slots[i].Item = nullptr;
				return true;
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Could not remove item!");
	return false;
}
