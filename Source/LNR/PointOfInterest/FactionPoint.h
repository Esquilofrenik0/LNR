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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBitloner* Bitloner;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EFaction> ControlFaction;
	virtual void BeginPlay() override;
};
