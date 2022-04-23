#pragma once
#include "LNR/Item/Item.h"
#include "Engine/DataTable.h"
#include "Dropable.generated.h"

USTRUCT(BlueprintType)
struct LNR_API FDropable : public FTableRowBase
{
	GENERATED_BODY()

	FDropable() : Item(nullptr), Amount(1), Chance(100)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItem> Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Chance;
};