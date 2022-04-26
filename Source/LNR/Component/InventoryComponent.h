#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LNR/Data/Slot.h"
#include "InventoryComponent.generated.h"

UCLASS()
class LNR_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UInventoryComponent();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FSlot> Slots;
};
