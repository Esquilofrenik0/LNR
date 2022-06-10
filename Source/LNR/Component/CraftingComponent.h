#pragma once
#include "CoreMinimal.h"
#include "CraftingComponent.generated.h"

UCLASS()
class LNR_API UCraftingComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCraftingComponent();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<class URecipe>> Book;
};
