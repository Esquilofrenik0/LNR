#include "Resource.h"

UResource::UResource()
{
	Stack = 100;
}

FString UResource::PrintItemData(bool withDescription)
{
	FString data = "Name: " + Name.ToString() + "\r";
	data += "Type: Resource\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	if(withDescription) data += "Description: " + Description + "\r";
	return data;
}
