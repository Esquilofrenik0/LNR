#include "AttributesComponent.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UAttributesComponent::UAttributesComponent()
{
	MaxHealth = 100 + (Vitality * 10);
	Health = MaxHealth;
	MaxStamina = 100 + (Agility * 10);
	Stamina = MaxStamina;
	MaxFocus = 100 + (Charisma * 10);
	Focus = MaxFocus;
	HealthRegeneration = 1 + (Vitality * 0.1);
	StaminaRegeneration = 1 + (Agility * 0.1);
	FocusRegeneration = 1 + (Charisma * 0.1);
	BaseDamage = Strength;
	BaseDefense = Charisma;
	Damage = BaseDamage;
	Defense = BaseDefense;
	MaxWanted = 100;
	WantedRegeneration = 0.01;
}

void UAttributesComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Level, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Xp, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Charisma, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Vitality, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Agility, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Wisdom, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Focus, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Wanted, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, BaseDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Damage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, BaseDefense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, MaxFocus, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, MaxWanted, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, StaminaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, FocusRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, WantedRegeneration, COND_None, REPNOTIFY_Always);
}

void UAttributesComponent::RefreshStats()
{
	if (GetOwningActor()->HasAuthority())
	{
		BaseDamage = Strength;
		BaseDefense = Charisma;
		MaxHealth = 100 + (Vitality * 10);
		HealthRegeneration = 1 + (Vitality * 0.1);
		MaxStamina = 100 + (Agility * 10);
		StaminaRegeneration = 1 + (Agility * 0.1);
		MaxFocus = 100 + (Charisma * 10);
		FocusRegeneration = 1 + (Charisma * 0.1);
	}
	else ServerRefreshStats();
}

void UAttributesComponent::Regenerate()
{
	ChangeHealth(HealthRegeneration);
	ChangeStamina(StaminaRegeneration);
	ChangeFocus(FocusRegeneration);
	ChangeWanted(-WantedRegeneration);
}

void UAttributesComponent::ChangeHealth(float value)
{
	Health += value;
	if (Health > MaxHealth) Health = MaxHealth;
	else if (Health < 0) Health = 0;
}

void UAttributesComponent::ChangeStamina(float value)
{
	Stamina += value;
	if (Stamina > MaxStamina) Stamina = MaxStamina;
	else if (Stamina < 0) Stamina = 0;
}

void UAttributesComponent::ChangeFocus(float value)
{
	Focus += value;
	if (Focus > MaxFocus) Focus = MaxFocus;
	else if (Focus < 0) Focus = 0;
}

void UAttributesComponent::ChangeWanted(float value)
{
	Wanted += value;
	if (Wanted > MaxWanted) Wanted = MaxWanted;
	else if (Wanted < 0) Wanted = 0;
}

FString UAttributesComponent::GetStatsText()
{
	return GetStrengthText() + "\n" + GetCharismaText() + "\n" + GetVitalityText() + "\n"
		+ GetAgilityText() + "\n" + GetWisdomText();
}

FString UAttributesComponent::GetAttributesText()
{
	return GetHealthText() + "\n" + GetStaminaText() + "\n" + GetFocusText() + "\n"
		+ GetDamageText() + "\n" + GetDefenseText();
}

FString UAttributesComponent::GetHealthText()
{
	return "Health: " + FString::FromInt(Health) + " / " + FString::FromInt(MaxHealth) + " (+" +
		FString::FromInt(HealthRegeneration) + "/s)";
}

FString UAttributesComponent::GetStaminaText()
{
	return "Stamina: " + FString::FromInt(Stamina) + " / " + FString::FromInt(MaxStamina) + " (+" +
		FString::FromInt(StaminaRegeneration) + "/s)";
}

FString UAttributesComponent::GetFocusText()
{
	return "Focus: " + FString::FromInt(Focus) + " / " + FString::FromInt(MaxFocus) + " (+" +
		FString::FromInt(FocusRegeneration) + "/s)";
}

FString UAttributesComponent::GetDamageText()
{
	return "Damage: " + FString::FromInt(Damage) + " (Base: " + FString::FromInt(BaseDamage) + ")";
}

FString UAttributesComponent::GetDefenseText()
{
	return "Defense: " + FString::FromInt(Defense) + " (Base: " + FString::FromInt(BaseDefense) + ")";
}

void UAttributesComponent::OnRep_Health(float oldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributesComponent, Health, oldHealth);
}

void UAttributesComponent::OnRep_Stamina(float oldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributesComponent, Stamina, oldStamina);
}

void UAttributesComponent::OnRep_Focus(float oldFocus)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributesComponent, Focus, oldFocus);
}

void UAttributesComponent::OnRep_Damage(float oldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributesComponent, Damage, oldDamage);
}

void UAttributesComponent::OnRep_Defense(float oldDefense)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributesComponent, Defense, oldDefense);
}

void UAttributesComponent::OnRep_Wanted(float oldWanted)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributesComponent, Wanted, oldWanted);
}
