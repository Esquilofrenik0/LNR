#include "RandomAttack.h"
#include "LNR/Body/Body.h"
#include "LNR/Component/CombatComponent.h"

void URandomAttack::PreAttack(ABody* body)
{
	Super::PreAttack(body);
	body->Combat->Combo = FMath::RandRange(0, body->Combat->GetMaxCombo() - 1);
}
