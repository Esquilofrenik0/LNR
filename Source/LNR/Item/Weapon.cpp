#include "Weapon.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/EquipmentComponent.h"
#include "LNR/Component/InventoryComponent.h"

UWeapon::UWeapon()
{
	Damage = 1.0f;
	Defense = 0.0f;
}

void UWeapon::UseItem(AHero* hero, int amount)
{
	hero->Equipment->EquipWeapon(this);
	hero->Inventory->Remove(this);
}

FString UWeapon::PrintItemData(bool withDescription)
{
	FString data = "Name: " + UMacro::GetRealName(this) + "\r";
	data += "Type: Weapon\r";
	data += "Damage: " + FString::SanitizeFloat(Damage) + "\r";
	data += "Defense: " + FString::SanitizeFloat(Defense) + "\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	if (withDescription) data += "Description: " + Description + "\r";
	return data;
}
