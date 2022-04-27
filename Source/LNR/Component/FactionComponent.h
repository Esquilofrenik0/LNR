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
	UFUNCTION(BlueprintCallable)
	bool CheckCitizenship(EFaction nFaction);
	UFUNCTION(BlueprintCallable)
	bool IsCitizen();
	UFUNCTION(BlueprintCallable)
	bool IsHostile(EFaction enemy);
};
