﻿#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InfoWidget.generated.h"

UCLASS()
class LNR_API UInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class UInfoComponent* Info;
};
