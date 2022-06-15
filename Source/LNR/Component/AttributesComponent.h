#pragma once
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributesComponent.generated.h"

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Level = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Xp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Strength = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Charisma = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Vitality = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Agility = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Wisdom = 1;

	UPROPERTY(BlueprintReadWrite)
	float BaseDamage;
	UPROPERTY(BlueprintReadWrite)
	float BaseDefense;
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHealth)
	float MaxHealth;
	UFUNCTION()
	virtual void OnRep_MaxHealth(float oldMaxHealth);
	UPROPERTY(BlueprintReadWrite)
	float MaxStamina;
	UPROPERTY(BlueprintReadWrite)
	float MaxEnergy;
	UPROPERTY(BlueprintReadWrite)
	float MaxWanted;
	UPROPERTY(BlueprintReadWrite)
	float HealthRegeneration;
	UPROPERTY(BlueprintReadWrite)
	float StaminaRegeneration;
	UPROPERTY(BlueprintReadWrite)
	float EnergyRegeneration;
	UPROPERTY(BlueprintReadWrite)
	float WantedRegeneration;

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Health)
	float Health;
	UFUNCTION()
	virtual void OnRep_Health(float oldHealth);
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Stamina)
	float Stamina;
	UFUNCTION()
	virtual void OnRep_Stamina(float oldStamina);
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Energy)
	float Energy;
	UFUNCTION()
	virtual void OnRep_Energy(float oldEnergy);
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

	UFUNCTION(BlueprintCallable)
	void Init();
	UFUNCTION(BlueprintCallable)
	void RefreshStats();
	UFUNCTION(BlueprintCallable)
	void Regenerate(float deltaTime);

	UFUNCTION(BlueprintCallable)
	void ChangeHealth(float value);
	UFUNCTION(BlueprintCallable)
	void ChangeStamina(float value);
	UFUNCTION(BlueprintCallable)
	void ChangeEnergy(float value);
	UFUNCTION(BlueprintCallable)
	void ChangeWanted(float value);

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() { return Health / MaxHealth; };
	UFUNCTION(BlueprintCallable)
	float GetStaminaPercent() { return Stamina / MaxStamina; };
	UFUNCTION(BlueprintCallable)
	float GetEnergyPercent() { return Energy / MaxEnergy; };
	UFUNCTION(BlueprintCallable)
	float GetWantedPercent() { return Wanted / MaxWanted; };

	UFUNCTION(BlueprintCallable)
	FString GetAttributesText();
	UFUNCTION(BlueprintCallable)
	FString GetStatsText();

	UFUNCTION(BlueprintCallable)
	FString GetStrengthText() { return "Strength: " + FString::FromInt(Strength); };
	UFUNCTION(BlueprintCallable)
	FString GetCharismaText() { return "Charisma: " + FString::FromInt(Charisma); };
	UFUNCTION(BlueprintCallable)
	FString GetVitalityText() { return "Vitality: " + FString::FromInt(Vitality); };
	UFUNCTION(BlueprintCallable)
	FString GetAgilityText() { return "Agility: " + FString::FromInt(Agility); };
	UFUNCTION(BlueprintCallable)
	FString GetWisdomText() { return "Wisdom: " + FString::FromInt(Wisdom); };

	UFUNCTION(BlueprintCallable)
	FString GetHealthText();
	UFUNCTION(BlueprintCallable)
	FString GetStaminaText();
	UFUNCTION(BlueprintCallable)
	FString GetEnergyText();
	UFUNCTION(BlueprintCallable)
	FString GetDamageText();
	UFUNCTION(BlueprintCallable)
	FString GetDefenseText();
	UFUNCTION(BlueprintCallable)
	FString GetWantedText();
};
