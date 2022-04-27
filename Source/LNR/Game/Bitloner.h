#pragma once
#include "CoreMinimal.h"
#include "LNR/Data/AvatarData.h"
#include "LNR/Data/FactionData.h"
#include "Bitloner.generated.h"

UCLASS()
class LNR_API UBitloner final : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAvatarGlobals AvatarGlobals;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFactionGlobals FactionGlobals;
};
