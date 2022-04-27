#pragma once
#include "CoreMinimal.h"
#include "Interactor.h"
#include "Container.generated.h"

UCLASS(Abstract)
class LNR_API AContainer : public AInteractor
{
	GENERATED_BODY()
public:
	AContainer();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInventoryComponent* Inventory;
	UPROPERTY(BlueprintReadWrite)
	class AHero* Hero;
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle CloseHandle;

	UFUNCTION(BlueprintCallable)
	virtual FString PrintContainerData();
	virtual void OnInteract_Implementation(AHero* nHero) override;

	UFUNCTION(BlueprintCallable)
	virtual void Close();
	UFUNCTION(BlueprintCallable)
	void CheckHeroDistance();
};
