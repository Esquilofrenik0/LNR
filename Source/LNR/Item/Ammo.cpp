#include "Ammo.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/EquipmentComponent.h"
#include "LNR/Component/InventoryComponent.h"

UAmmo::UAmmo()
{
	Stack = 999;
}

void UAmmo::UseItem(AHero* hero, int amount)
{
	hero->Equipment->EquipAmmo(this, amount);
	hero->Inventory->Remove(this, amount);
}

FString UAmmo::PrintItemData(bool withDescription)
{
	FString data = "Name: " + UMacro::GetRealName(this) + "\r";
	data += "Type: Ammo\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	if(withDescription) data += "Description: " + Description + "\r";
	return data;
}
