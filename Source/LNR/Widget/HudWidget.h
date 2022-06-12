#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "LNR/Game/HudBitloner.h"
#include "HudWidget.generated.h"

UCLASS(Abstract)
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
	UImage* InteractionType;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* WarningText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UActionBarWidget* ActionBarWidget;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UAttributesWidget* AttributesWidget;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UCompassWidget* CompassWidget;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UInventoryWidget* InventoryWidget;
	void Init(AHudBitloner* nHud);

    FTimerHandle PrintHandle;
	UFUNCTION(BlueprintCallable)
	void Print(FString txt);
	UFUNCTION(BlueprintCallable)
	void ClearPrint();
	
};
