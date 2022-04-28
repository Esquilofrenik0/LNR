#pragma once
#include "LNR/Body/Body.h"
#include "Engine/DataTable.h"
#include "SpawnData.generated.h"

USTRUCT(BlueprintType)
struct LNR_API FSpawnTemplate : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ASoul> Soul;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Weight;

	FSpawnTemplate()
	{
		Soul = nullptr;
		Weight = 1;
	}
};

UCLASS(Abstract, Blueprintable, BlueprintType, CollapseCategories, DefaultToInstanced, EditInlineNew)
class LNR_API USpawnData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSpawnTemplate> SpawnData;
};
