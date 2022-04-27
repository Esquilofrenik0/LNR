#include "Humanoid.h"
#include "LNR/Component/AttributesComponent.h"
#include "LNR/Component/EquipmentComponent.h"

AHumanoid::AHumanoid()
{
	Equipment = CreateDefaultSubobject<UEquipmentComponent>("Equipment");
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
