#include "Buildable.h"
#include "LNR/Body/Hero.h"

UBuildable::UBuildable()
{
	Stack = 100;
}

void UBuildable::UseItem(AHero* hero, int amount)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Red, "Buildable - Use Item not Implemented!");
	// Print("Started Building " + Id.ToString());
	// hero->StartBuild(this);
}

FString UBuildable::PrintItemData(bool withDescription)
{
	FString data = "Name: " + UMacro::GetRealName(this) + "\r";
	data += "Type: Buildable\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	if(withDescription) data += "Description: " + Description + "\r";
	return data;
}

