#pragma once
#include "CoreMinimal.h"
#include "Weapon.h"
#include "Shield.generated.h"

UCLASS(Abstract)
class LNR_API UShield : public UWeapon
{
	GENERATED_BODY()
public:
	UShield();
};
