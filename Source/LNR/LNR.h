#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EDamageType
{
	Melee = 0,
	Ranged = 1,
	Physics = 2,
	Pickup = 3,
};

static void Print(FString print);
static void Print(int print);
static void Print(float print);
