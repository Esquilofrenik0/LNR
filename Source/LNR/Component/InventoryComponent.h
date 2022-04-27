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
	UFUNCTION(BlueprintCallable)
	bool Add(UItem* item, int amount = 1);
	UFUNCTION(BlueprintCallable)
	bool Remove(UItem* item, int amount = 1);
	UFUNCTION(BlueprintCallable)
	bool Retrieve(UInventoryComponent* to, UItem* item, int amount = 1);
	UFUNCTION(BlueprintCallable)
	bool Store(UInventoryComponent* from, UItem* item, int amount = 1);
};
