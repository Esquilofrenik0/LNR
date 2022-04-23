#include "Outfit.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/ApparelComponent.h"
// #include "LNR/Component/InventoryComponent.h"

void UOutfit::UseItem(AHero* hero, int amount)
{
	Print("Outfit UseItem Not Implemented!");	
	// hero->Apparel->EquipOutfit(this);
	// hero->Inventory->RemoveItem(this);
}

FString UOutfit::PrintItemData(bool withDescription)
{
	FString data = "Name: " + Name.ToString() + "\r";
	data += "Type: Outfit\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	if(withDescription) data += "Description: " + Description + "\r";
	return data;
}

