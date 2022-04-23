#pragma once
#include "Engine/DataTable.h"
#include "LNR/Data/Slot.h"
#include "Schema.generated.h"

USTRUCT(BlueprintType)
struct LNR_API FSchema : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FSlotTemplate Result;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FSlotTemplate> Cost;
};
