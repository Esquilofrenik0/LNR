#pragma once
#include "Engine/DataTable.h"
#include "BookData.generated.h"

USTRUCT(BlueprintType)
struct LNR_API FBookData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString BookName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> BookPages;
};

