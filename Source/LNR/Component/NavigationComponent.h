#pragma once
#include "CoreMinimal.h"
#include "NavigationComponent.generated.h"

UCLASS()
class LNR_API UNavigationComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UNavigationComponent();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<class UMarkerComponent*> Marker;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int DrawDistance = 1000000;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> Discovered;
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void Init();
};
