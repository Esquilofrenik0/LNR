#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "LNR/Data/AvatarData.h"
#include "LNR/Data/FactionData.h"
#include "BitlonerGameMode.generated.h"

UCLASS()
class LNR_API ABitlonerGameMode final : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAvatarGlobals AvatarGlobals;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFactionGlobals FactionGlobals;
};
