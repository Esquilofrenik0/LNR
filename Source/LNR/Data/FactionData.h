#pragma once
#include "Engine/DataTable.h"
#include "LNR/Component/FactionComponent.h"
#include "LNR/Data/SpawnData.h"
#include "FactionData.generated.h"

USTRUCT(BlueprintType)
struct LNR_API FFactionData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EFaction> Faction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USpawnData> SpawnData;
};

USTRUCT(BlueprintType)
struct LNR_API FFactionGlobals : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FFactionData> Faction;
};
