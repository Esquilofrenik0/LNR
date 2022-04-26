#include "Aid.h"
#include "LNR/Body/Body.h"
#include "LNR/Component/AttributesComponent.h"

UAid::UAid()
{
	HealthRestore = 0.0f;
	StaminaRestore = 0.0f;
	EnergyRestore = 0.0f;
}

void UAid::Consume_Implementation(ABody* body)
{
	if (HealthRestore != 0) { body->Attributes->ChangeHealth(HealthRestore); }
	if (StaminaRestore != 0) { body->Attributes->ChangeStamina(StaminaRestore); }
	if (EnergyRestore != 0) { body->Attributes->ChangeEnergy(EnergyRestore); }
}
