#pragma once
#include "CoreMinimal.h"
#include "PointOfInterest.h"
#include "LNR/Component/FactionComponent.h"
#include "LNR/Data/SpawnData.h"
#include "FactionPoint.generated.h"

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class LNR_API UFactionPoint : public UPointOfInterest
{
	GENERATED_BODY()
public:
	UFactionPoint();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	UFactionComponent* Faction;
};
