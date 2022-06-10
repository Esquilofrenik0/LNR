#include "InventoryComponent.h"
#include "Net/UnrealNetwork.h"

UInventoryComponent::UInventoryComponent()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
	Slots.Init(FSlot(), 64);
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UInventoryComponent, Slots);
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

bool UInventoryComponent::Retrieve(UInventoryComponent* to, UItem* item, int amount)
{
	if (to->Add(item, amount))
	{
		Remove(item, amount);
		return true;
	}
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Could not retrieve item!");
	return false;
}

bool UInventoryComponent::Store(UInventoryComponent* from, UItem* item, int amount)
{
	if (Add(item, amount))
	{
		from->Remove(item, amount);
		return true;
	}
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Could not store item!");
	return false;
}

bool UInventoryComponent::Contains(UItem* item, int amount)
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		if(Slots[i].Item == item && Slots[i].Amount >= amount) return true;
	}
	return false;
}
