#pragma once
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributesComponent.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UENUM(BlueprintType)
enum EStats
{
	Strength,
	Charisma,
	Vitality,
	Agility,
	Wisdom
};

UCLASS()
class LNR_API UAttributesComponent : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAttributesComponent();

	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
	int Level = 1;
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere)
	float Xp = 0;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int Strength = 1;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int Charisma = 1;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int Vitality = 1;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int Agility = 1;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int Wisdom = 1;

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Health)
	float Health;
	UFUNCTION()
	virtual void OnRep_Health(float oldHealth);
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Stamina)
	float Stamina;
	UFUNCTION()
	virtual void OnRep_Stamina(float oldStamina);
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Focus)
	float Focus;
	UFUNCTION()
	virtual void OnRep_Focus(float oldFocus);
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Damage)
	float Damage;
	UFUNCTION()
	virtual void OnRep_Damage(float oldDamage);
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Defense)
	float Defense;
	UFUNCTION()
	virtual void OnRep_Defense(float oldDefense);
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Wanted)
	float Wanted = 0;
	UFUNCTION()
	virtual void OnRep_Wanted(float oldWanted);

	UPROPERTY(Replicated, BlueprintReadWrite)
	float BaseDamage;
	UPROPERTY(Replicated, BlueprintReadWrite)
	float BaseDefense;
	UPROPERTY(Replicated, BlueprintReadWrite)
	float MaxHealth;
	UPROPERTY(Replicated, BlueprintReadWrite)
	float MaxStamina;
	UPROPERTY(Replicated, BlueprintReadWrite)
	float MaxFocus;
	UPROPERTY(Replicated, BlueprintReadWrite)
	float MaxWanted;
	UPROPERTY(Replicated, BlueprintReadWrite)
	float HealthRegeneration;
	UPROPERTY(Replicated, BlueprintReadWrite)
	float StaminaRegeneration;
	UPROPERTY(Replicated, BlueprintReadWrite)
	float FocusRegeneration;
	UPROPERTY(Replicated, BlueprintReadWrite)
	float WantedRegeneration;

	void Regenerate();

	UFUNCTION(BlueprintCallable)
	void ChangeHealth(float value);
	UFUNCTION(BlueprintCallable)
	void ChangeStamina(float value);
	UFUNCTION(BlueprintCallable)
	void ChangeFocus(float value);
	UFUNCTION(BlueprintCallable)
	void ChangeWanted(float value);

	UFUNCTION(BlueprintCallable)
	void RefreshStats();
	UFUNCTION(Server, Reliable)
	void ServerRefreshStats();
	void ServerRefreshStats_Implementation() { RefreshStats(); }

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() { return Health / MaxHealth; };
	UFUNCTION(BlueprintCallable)
	float GetStaminaPercent() { return Stamina / MaxStamina; };
	UFUNCTION(BlueprintCallable)
	float GetFocusPercent() { return Focus / MaxFocus; };
	UFUNCTION(BlueprintCallable)
	float GetHatePercent() { return Wanted / MaxWanted; };

	UFUNCTION(BlueprintCallable)
	FString GetStatsText();
	UFUNCTION(BlueprintCallable)
	FString GetAttributesText();

	UFUNCTION(BlueprintCallable)
	FString GetStrengthText() { return "Strength: " + FString::FromInt(Strength); }

	UFUNCTION(BlueprintCallable)
	FString GetCharismaText() { return "Charisma: " + FString::FromInt(Charisma); }

	UFUNCTION(BlueprintCallable)
	FString GetVitalityText() { return "Vitality: " + FString::FromInt(Vitality); }

	UFUNCTION(BlueprintCallable)
	FString GetAgilityText() { return "Agility: " + FString::FromInt(Agility); }

	UFUNCTION(BlueprintCallable)
	FString GetWisdomText() { return "Wisdom: " + FString::FromInt(Wisdom); }

	UFUNCTION(BlueprintCallable)
	FString GetHealthText();
	UFUNCTION(BlueprintCallable)
	FString GetStaminaText();
	UFUNCTION(BlueprintCallable)
	FString GetFocusText();
	UFUNCTION(BlueprintCallable)
	FString GetDamageText();
	UFUNCTION(BlueprintCallable)
	FString GetDefenseText();
};
