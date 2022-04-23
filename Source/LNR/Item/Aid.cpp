#include "Aid.h"
#include "LNR/Body/Body.h"
// #include "LNR/Component/AttributesComponent.h"

UAid::UAid()
{
	HealthRestore = 0.0f;
	StaminaRestore = 0.0f;
	FocusRestore = 0.0f;
}

void UAid::Consume_Implementation(ABody* body)
{
	Print("Aid Consume Not Implemented!");	
	// if (HealthRestore != 0) { body->Attributes->ChangeHealth(HealthRestore); }
	// if (StaminaRestore != 0) { body->Attributes->ChangeStamina(StaminaRestore); }
	// if (FocusRestore != 0) { body->Attributes->ChangeFocus(FocusRestore); }
}
