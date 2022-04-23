#include "Weapon.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/EquipmentComponent.h"
// #include "LNR/Component/InventoryComponent.h"

UWeapon::UWeapon()
{
	Damage = 1.0f;
	Defense = 0.0f;
}

void UWeapon::UseItem(AHero* hero, int amount)
{
	Print("Weapon UseItem Not Implemented!");	
	// hero->Equipment->EquipWeapon(this);
	// hero->Inventory->RemoveItem(this);
}

FString UWeapon::PrintItemData(bool withDescription)
{
	FString data = "Name: " + Name.ToString() + "\r";
	data += "Type: Weapon\r";
	data += "Damage: " + FString::SanitizeFloat(Damage) + "\r";
	data += "Defense: " + FString::SanitizeFloat(Defense) + "\r";
	data += "Price: " + FString::SanitizeFloat(Price) + "\r";
	data += "Weight: " + FString::SanitizeFloat(Weight) + "\r";
	if (withDescription) data += "Description: " + Description + "\r";
	return data;
}

void UWeapon::Attack(ABody* body, USkeletalMeshComponent* weapon)
{
	Print("Attacking with weapon");
}
