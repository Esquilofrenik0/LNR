#pragma once
#include "Engine/DataTable.h"
#include "FactionData.generated.h"

UENUM()
enum FFaction { Empire, Survivor, Biohacker, Inquisitor, Mutant, Rogue, Feral, Critter };

USTRUCT(BlueprintType)
struct LNR_API FFactionData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<FFaction> Faction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Color;
};

USTRUCT(BlueprintType)
struct LNR_API FFactionGlobals : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FFactionData> Faction;
};
