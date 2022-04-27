#pragma once
#include "Engine/DataTable.h"
#include "LNR/Item/Outfit.h"
#include "AvatarData.generated.h"

USTRUCT(BlueprintType)
struct LNR_API FAvatarData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Body = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hair = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Beard = 0;
};

USTRUCT(BlueprintType)
struct LNR_API FAvatarGlobals : public FTableRowBase
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UOutfit>> Outfit;
};
