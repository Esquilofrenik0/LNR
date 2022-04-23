#pragma once
#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Ability.generated.h"

UENUM(BlueprintType)
enum EAbilityInput
{
	Confirm = 0,
	Cancel = 1,
	Passive = 2,
	Attack = 3,
	Block = 4,
	Sprint = 5,
	Dodge = 6,
	Reload = 7,
	Action1 = 8,
	Action2 = 9,
	Action3 = 10,
	Action4 = 11
};

UCLASS()
class LNR_API UAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UAbility();
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	TEnumAsByte<EAbilityInput> AbilityInput = EAbilityInput::Passive;
};
