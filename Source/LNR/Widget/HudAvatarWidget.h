﻿#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudAvatarWidget.generated.h"

UCLASS(Abstract)
class LNR_API UHudAvatarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class AHudMenu* Hud;
	void Init(AHudMenu* nHud);
};
