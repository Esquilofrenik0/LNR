#pragma once
#include "CoreMinimal.h"
#include "Weapon.h"
#include "Melee.generated.h"

UCLASS(Abstract)
class LNR_API UMelee : public UWeapon
{
	GENERATED_BODY()
public:
	virtual void Attack(class ABody* body, class USkeletalMeshComponent* weapon) override;
};
