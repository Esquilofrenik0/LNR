#pragma once
#include "CoreMinimal.h"
#include "PointOfInterest.h"
#include "FactionPoint.generated.h"

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class LNR_API UFactionPoint : public UPointOfInterest
{
	GENERATED_BODY()
public:
	UFactionPoint();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	class UFactionComponent* Faction;
	virtual void BeginPlay() override;
};
