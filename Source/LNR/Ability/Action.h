#pragma once
#include "CoreMinimal.h"
#include "Ability.h"
#include "Action.generated.h"

UCLASS()
class LNR_API UAction : public UAbility
{
	GENERATED_BODY()
public:
	UAction();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) UTexture2D* Icon;
};
