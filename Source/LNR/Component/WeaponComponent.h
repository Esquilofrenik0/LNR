#pragma once
#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LNR_API UWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:
	UWeaponComponent();
};
