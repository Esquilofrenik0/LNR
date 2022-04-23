#pragma once
#include "CoreMinimal.h"
#include "InfoCanvas.h"
#include "Components/WidgetComponent.h"
#include "InfoWidget.generated.h"

UCLASS()
class LNR_API UInfoWidget : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Icon;
	UPROPERTY(BlueprintReadWrite)
	FString Text;
	UPROPERTY(BlueprintReadWrite)
	UInfoCanvas* InfoCanvas;

	UInfoWidget()
	{
		ToggleVisibility(false);
		SetDrawAtDesiredSize(false);
		SetDrawSize(FVector2D(120, 40));
		TickMode = ETickMode::Automatic;
		SetWindowFocusable(false);
		SetComponentTickEnabled(false);
		SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	UFUNCTION(BlueprintCallable)
	void SetCanvas(UTexture2D* nIcon, FString nText)
	{
		Icon = nIcon;
		Text = nText;
		if(InfoCanvas == nullptr) InfoCanvas = Cast<UInfoCanvas>(GetWidget());
		if (InfoCanvas)
		{
			if (Icon) InfoCanvas->Icon = Icon;
			InfoCanvas->Text = Text;
		}
	}

	UFUNCTION(BlueprintCallable)
	void SetCanvasText(FString nText)
	{
		Text = nText;
		if(InfoCanvas == nullptr) InfoCanvas = Cast<UInfoCanvas>(GetWidget());
		if (InfoCanvas) InfoCanvas->Text = Text;
	}
};