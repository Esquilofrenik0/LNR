#pragma once
#include "LNR/Item/Item.h"
#include "Engine/DataTable.h"
#include "LNR/Item/Ammo.h"
#include "LNR/Item/Consumable.h"
#include "Slot.generated.h"

USTRUCT(BlueprintType)
struct LNR_API FVendorSlot : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItem> Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Probability;

	FVendorSlot()
	{
		Item = nullptr;
		Amount = 1;
		Probability = 100;
	}
};

USTRUCT(BlueprintType)
struct LNR_API FConsumableSlot : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	UConsumable* Consumable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Amount;

	FConsumableSlot()
	{
		Consumable = nullptr;
		Amount = 1;
	}

	FConsumableSlot(UConsumable* consumable, int amount)
	{
		Consumable = consumable;
		Amount = amount;
	}
};

USTRUCT(BlueprintType)
struct LNR_API FAmmoSlot : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	UAmmo* Ammo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Amount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Loaded;

	FAmmoSlot()
	{
		Ammo = nullptr;
		Amount = 0;
		Loaded = 0;
	}

	FAmmoSlot(UAmmo* ammo, int amount, int loaded)
	{
		Ammo = ammo;
		Amount = amount;
		Loaded = loaded;
	}
};

USTRUCT(BlueprintType)
struct LNR_API FSlot : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	UItem* Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Amount;

	FSlot()
	{
		Item = nullptr;
		Amount = 1;
	}

	FSlot(UItem* item, int amount)
	{
		Item = item;
		Amount = amount;
	}
};

USTRUCT(BlueprintType)
struct LNR_API FSlotTemplate : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItem> Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Amount;

	FSlotTemplate()
	{
		Item = nullptr;
		Amount = 1;
	}
	
	FSlotTemplate(TSubclassOf<UItem> item, int amount)
	{
		Item = item;
		Amount = amount;
	}
};
