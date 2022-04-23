#pragma once
#include "CoreMinimal.h"
#include "Item.h"
#include "Ammo.generated.h"

UCLASS(Abstract)
class LNR_API UAmmo : public UItem
{
	GENERATED_BODY()
public:
	UAmmo();
	virtual void UseItem(AHero* hero, int amount) override;
	virtual FString PrintItemData(bool withDescription) override;
};
