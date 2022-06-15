#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CompassWidget.generated.h"

UCLASS(Abstract)
class LNR_API UCompassWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class UMarkerWidget> MarkerTemplate;
	UPROPERTY(BlueprintReadWrite)
	class AHero* Hero;
	UPROPERTY(BlueprintReadWrite)
	TArray<UMarkerWidget*> Marker;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UOverlay* Panel;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UImage* Compass;

	UPROPERTY(BlueprintReadWrite)
	class UMaterialInstanceDynamic* CompassMaterial;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void Init(class AHero* nHero);
	void Refresh();
	void DrawMarker(class UMarkerComponent* nMarker);
	void HideMarker(const class UMarkerComponent* nMarker);
};
