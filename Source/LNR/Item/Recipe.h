#pragma once
#include "CoreMinimal.h"
#include "Item.h"
#include "LNR/Data/Slot.h"
#include "Recipe.generated.h"

UCLASS(Abstract)
class LNR_API URecipe : public UItem
{
	GENERATED_BODY()
public:
	URecipe();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FSlotTemplate Result;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FSlotTemplate> Cost;
	virtual FString PrintItemData(bool withDescription) override;
};
