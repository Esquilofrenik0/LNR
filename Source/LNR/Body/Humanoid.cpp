#include "Humanoid.h"
#include "LNR/Component/AttributesComponent.h"
#include "LNR/Component/CombatComponent.h"
#include "LNR/Component/EquipmentComponent.h"

AHumanoid::AHumanoid()
{
	Equipment = CreateDefaultSubobject<UEquipmentComponent>("Equipment");
}

void AHumanoid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Equipment->Setup(this);
}

void AHumanoid::RefreshAttributes()
{
	Super::RefreshAttributes();
	if (UWeapon* mw = Equipment->GetWeapon(0))
	{
		Attributes->Damage += mw->Damage;
		Attributes->Defense += mw->Defense;
	}
	if (UWeapon* ow = Equipment->GetWeapon(1))
	{
		Attributes->Damage += ow->Damage;
		Attributes->Defense += ow->Defense;
	}
}

void AHumanoid::ActivateConsumable(int index)
{
	if (HasAuthority())
	{
		if (Equipment->Consumable[index].Consumable && Equipment->Consumable[index].Amount > 0)
		{
			if (Combat->State == Idle || Combat->State == Blocking)
			{
				Equipment->Consumable[index].Consumable->UseConsumable(this);
				Equipment->Consumable[index].Amount -= 1;
				if (Equipment->Consumable[index].Amount <= 0) Equipment->Consumable[index].Consumable = nullptr;
			}
		}
	}
	else ServerActivateConsumable(index);
}
