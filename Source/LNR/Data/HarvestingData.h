#pragma once
#include "Engine/DataTable.h"
#include "LNR/Item/Resource.h"
#include "HarvestingData.generated.h"

USTRUCT(BlueprintType)
struct LNR_API FHarvestingData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, UAnimMontage*> HarvestingMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, USkeletalMesh*> HarvestingUtensil;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, TSubclassOf<UResource>> HarvestingReward;
};
