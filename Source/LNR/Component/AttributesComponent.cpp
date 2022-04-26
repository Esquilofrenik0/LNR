#include "AttributesComponent.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UAttributesComponent::UAttributesComponent()
{
	RefreshStats();
	Damage = BaseDamage;
	Defense = BaseDefense;
	Health = MaxHealth;
	Stamina = MaxStamina;
	Energy = MaxEnergy;
	Wanted = 0;
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
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Energy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Wanted, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, BaseDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Damage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, BaseDefense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, Defense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, MaxEnergy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, MaxWanted, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, StaminaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, EnergyRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributesComponent, WantedRegeneration, COND_None, REPNOTIFY_Always);
}

void UAttributesComponent::RefreshStats()
{
	BaseDamage = Strength;
	BaseDefense = Charisma;
	MaxHealth = 100 + (Vitality * 10);
	MaxStamina = 100 + (Agility * 10);
	MaxEnergy = 100 + (Wisdom * 10);
	HealthRegeneration = Vitality * 0.5;
	StaminaRegeneration = Agility * 0.5;
	EnergyRegeneration = Wisdom * 0.5;
}

void UAttributesComponent::Regenerate(float deltaTime)
{
	ChangeHealth(HealthRegeneration * deltaTime);
	ChangeStamina(StaminaRegeneration * deltaTime);
	ChangeEnergy(EnergyRegeneration * deltaTime);
	ChangeWanted(-WantedRegeneration * deltaTime);
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

void UAttributesComponent::ChangeEnergy(float value)
{
	Energy += value;
	if (Energy > MaxEnergy) Energy = MaxEnergy;
	else if (Energy < 0) Energy = 0;
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
	return GetHealthText() + "\n" + GetStaminaText() + "\n" + GetEnergyText() + "\n"
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

FString UAttributesComponent::GetEnergyText()
{
	return "Focus: " + FString::FromInt(Energy) + " / " + FString::FromInt(MaxEnergy) + " (+" +
		FString::FromInt(EnergyRegeneration) + "/s)";
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

void UAttributesComponent::OnRep_Energy(float oldEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributesComponent, Energy, oldEnergy);
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
