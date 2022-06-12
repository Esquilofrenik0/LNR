#pragma once
#include "CoreMinimal.h"
#include "FactionPoint.h"
#include "LNR/Component/FactionComponent.h"
#include "LNR/Data/SpawnData.h"
#include "ControlPoint.generated.h"

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class LNR_API UControlPoint : public UFactionPoint
{
	GENERATED_BODY()
public:
	UControlPoint();

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EFaction> ContestingFaction;
	UPROPERTY(BlueprintReadWrite)
	TArray<class ABody*> Bodies;
	UPROPERTY(BlueprintReadWrite)
	float Influence;
	UPROPERTY(BlueprintReadWrite)
	float IncrementAmount;
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle InfluenceTimer;

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void AddBody(ABody* body);
	UFUNCTION(BlueprintCallable)
	void RemoveBody(ABody* body);
	UFUNCTION(BlueprintCallable)
	void StartIncreaseInfluence();
	UFUNCTION(BlueprintCallable)
	void IncreaseInfluence();
	UFUNCTION(BlueprintCallable)
	void StartDecreaseInfluence();
	UFUNCTION(BlueprintCallable)
	void DecreaseInfluence();
	UFUNCTION(BlueprintCallable)
	EFaction GetWinningFaction();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSetControl);

	UPROPERTY(BlueprintAssignable)
	FSetControl SetControl;
};
