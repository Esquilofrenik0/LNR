#pragma once
#include "CoreMinimal.h"
#include "Container.h"
#include "Tombstone.generated.h"

UCLASS(Abstract)
class LNR_API ATombstone : public AContainer
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int MaxAliveTime = 60;
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle DestroyHandle;
	virtual void BeginPlay() override;
	virtual void OnInteract_Implementation(AHero* nHero) override;
	virtual void Close() override;
	void DestroyThis();
};
