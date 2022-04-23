#include "ActionComponent.h"

void UActionComponent::InitializeAbilities()
{
	for (TSubclassOf<UAbility> ability : Default)
	{
		if (ability) GiveAbility(FGameplayAbilitySpec(ability, 1, ability.GetDefaultObject()->AbilityInput));
	}
	for (int i=0; i<ActionBar.Num(); i++) AddAction(ActionBar[i],i);
}

void UActionComponent::AddAction(TSubclassOf<UAction> action, int slot)
{
	if (action)
	{
		if(slot == 0) GiveAbility(FGameplayAbilitySpec(action, 1, Action1));
		else if(slot == 1) GiveAbility(FGameplayAbilitySpec(action, 1, Action2));
		else if(slot == 2) GiveAbility(FGameplayAbilitySpec(action, 1, Action3));
		else if(slot == 3) GiveAbility(FGameplayAbilitySpec(action, 1, Action4));
	}
}

void UActionComponent::RemoveAction(int slot)
{
	if(slot == 0) ClearAbility(FindAbilitySpecFromInputID(Action1)->Handle);
	else if(slot == 1) ClearAbility(FindAbilitySpecFromInputID(Action2)->Handle);
	else if(slot == 2) ClearAbility(FindAbilitySpecFromInputID(Action3)->Handle);
	else if(slot == 3) ClearAbility(FindAbilitySpecFromInputID(Action4)->Handle);
}

void UActionComponent::Execute(EAbilityInput input)
{
	if (FGameplayAbilitySpec* spec = FindAbilitySpecFromInputID(input)) TryActivateAbility(spec->Handle);
}
