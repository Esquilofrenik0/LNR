#pragma once
#include "Engine/DataTable.h"
#include "HumanData.generated.h"

USTRUCT(BlueprintType)
struct LNR_API FHumanData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkeletalMesh*> Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkeletalMesh*> Hair;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkeletalMesh*> Beard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Simglove;
};
