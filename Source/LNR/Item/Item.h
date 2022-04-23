#pragma once
#include "CoreMinimal.h"
#include "LNR/LNR.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType, CollapseCategories, DefaultToInstanced, EditInlineNew)
class LNR_API UItem : public UDataAsset
{
	GENERATED_BODY()
public:
	UItem();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
	
	virtual void UseItem(class AHero* hero, int amount = 1);
	UFUNCTION(BlueprintCallable)
	bool Compare(UItem* item);
	UFUNCTION(BlueprintCallable)
	virtual FString PrintItemData(bool withDescription = false);
};
