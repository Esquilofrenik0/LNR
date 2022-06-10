#include "Item.h"
#include "LNR/Body/Hero.h"

UItem::UItem()
{
	Price = 1;
	Weight = 1;
	Stack = 1;
	Description = "";
}

void UItem::UseItem(AHero* hero, int amount)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Red, UMacro::GetRealName(this) + " used");
}

bool UItem::Compare(UItem* item)
{
	if (item == nullptr) return false;
	else if (UMacro::GetRealName(item) == UMacro::GetRealName(this)) return true;
	else return false;
}

FString UItem::PrintItemData(bool withDescription)
{
	FString data = "Name: " + UMacro::GetRealName(this) + "\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	if (withDescription) data += "Description: " + Description + "\r";
	return data;
}
