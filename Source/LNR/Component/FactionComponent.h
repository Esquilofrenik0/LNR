#pragma once
#include "CoreMinimal.h"
#include "FactionComponent.generated.h"

UENUM()
enum EFaction
{
	Empire = 0,
	Survivor = 1,
	Biohacker = 2,
	Inquisitor = 3,
	Mutant = 4,
	Rogue = 5,
	Feral = 6,
	Critter = 7
};

UCLASS()
class LNR_API UFactionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFactionComponent();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EFaction> Faction;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBitloner* Bitloner;
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	bool CheckCitizenship(EFaction nFaction);
	UFUNCTION(BlueprintCallable)
	bool IsCitizen();
	UFUNCTION(BlueprintCallable)
	bool IsHostile(EFaction enemy);
	UFUNCTION(BlueprintCallable)
	UTexture2D* GetFactionIcon() const;
	UFUNCTION(BlueprintCallable)
	FLinearColor GetFactionColor() const;
	UFUNCTION(BlueprintCallable)
	TSubclassOf<class USpawnData> GetFactionSpawnData() const;
};
