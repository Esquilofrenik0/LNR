#pragma once
#include "CoreMinimal.h"
#include "Item.h"
#include "Outfit.generated.h"

UCLASS(Abstract)
class LNR_API UOutfit : public UItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Mask; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HideHelmet = false;

	virtual void UseItem(AHero* hero, int amount) override;
	virtual FString PrintItemData(bool withDescription) override;
};
