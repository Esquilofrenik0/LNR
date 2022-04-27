﻿#pragma once
#include "CoreMinimal.h"
#include "LNR/Data/AvatarData.h"
#include "LNR/Data/FactionData.h"
#include "LNR/Interactor/Tombstone.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATombstone> Tombstone;
};
