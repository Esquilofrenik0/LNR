#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LNR/Data/HumanData.h"
#include "LNRGameMode.generated.h"

UCLASS()
class LNR_API ALNRGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALNRGameMode();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHumanData HumanData;
};
