﻿#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "LNR/Game/HudBitloner.h"
#include "HudWidget.generated.h"

UCLASS()
class LNR_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	AHudBitloner* Hud;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* CrossHairImage;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* InteractionImage;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UActionBarWidget* ActionBarWidget;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UAttributesWidget* AttributesWidget;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UInventoryWidget* InventoryWidget;
	void Init(AHudBitloner* nHud);
};
