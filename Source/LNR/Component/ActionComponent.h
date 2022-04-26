#pragma once
#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "LNR/Ability/Action.h"
#include "ActionComponent.generated.h"

UCLASS()
class LNR_API UActionComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	UActionComponent();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UAbility>> Default;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UAction>> ActionBar;
	virtual void InitializeAbilities();
	void AddAction(TSubclassOf<UAction> action, int slot); 
	void RemoveAction(int slot);
	void Execute(EAbilityInput input);
};
