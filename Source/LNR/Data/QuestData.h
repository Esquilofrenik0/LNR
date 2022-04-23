#pragma once
#include "Engine/DataTable.h"
#include "LNR/Data/Slot.h"
#include "QuestData.generated.h"

USTRUCT(BlueprintType)
struct LNR_API FQuestReward : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Xp = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Gold = 0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<UItem>> Items;

	FQuestReward()
	{
		Xp = 0;
		Gold = 0;
		Items.Empty();
	}

	FQuestReward(int xp, int gold, TArray<TSubclassOf<UItem>> items)
	{
		Xp = xp;
		Gold = gold;
		Items = items;
	}
};


USTRUCT(BlueprintType)
struct LNR_API FQuestData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Description;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FQuestReward Reward;

	FQuestData()
	{
		Name = "";
		Description = "";
		Reward = FQuestReward();
	}

	FQuestData(FString name, FString description, FQuestReward reward)
	{
		Name = name;
		Description = description;
		Reward = reward;
	}
};
