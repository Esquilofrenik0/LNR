#include "Armor.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/ApparelComponent.h"
#include "LNR/Component/InventoryComponent.h"

UArmor::UArmor()
{
	Defense = 0.0f;
	HideHair = false;
}

void UArmor::UseItem(AHero* hero, int amount)
{
	hero->Apparel->EquipArmor(this);
	hero->Inventory->Remove(this);
}

FString UArmor::PrintItemData(bool withDescription)
{
	FString data = "Name: " + UMacro::GetRealName(this) + "\r";
	data += "Type: Armor\r";
	data += "Defense: " + FString::SanitizeFloat(Defense) + "\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	if(withDescription) data += "Description: " + Description + "\r";
	return data;
}

