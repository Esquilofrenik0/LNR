#pragma once
#include "CoreMinimal.h"
#include "Weapon.h"
#include "Gun.generated.h"

UCLASS(Abstract)
class LNR_API UGun : public UWeapon
{
	GENERATED_BODY()
public:
	UGun();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* ReloadMontage;
};
