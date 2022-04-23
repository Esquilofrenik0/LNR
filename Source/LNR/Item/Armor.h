#pragma once
#include "CoreMinimal.h"
#include "Item.h"
#include "Armor.generated.h"

UENUM()
enum EArmorSlot
{
	Head = 0 UMETA(DisplayName = "Head"),
	Back = 1 UMETA(DisplayName = "Back"),
	Chest = 2 UMETA(DisplayName = "Chest"),
	Legs = 3 UMETA(DisplayName = "Legs"),
	Feet = 4 UMETA(DisplayName = "Feet")
};

UCLASS(Abstract)
class LNR_API UArmor : public UItem
{
	GENERATED_BODY()
public:
	UArmor();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EArmorSlot> Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HideHair;

	virtual void UseItem(AHero* hero, int amount) override;
	virtual FString PrintItemData(bool withDescription) override;
};
