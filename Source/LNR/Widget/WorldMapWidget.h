#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorldMapWidget.generated.h"

UCLASS(Abstract)
class LNR_API UWorldMapWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class UMarkerWidget> MarkerTemplate;
	UPROPERTY(BlueprintReadWrite)
	class APlayor* Player;
	UPROPERTY(BlueprintReadWrite)
	TArray<UMarkerWidget*> Marker;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UOverlay* Panel;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UImage* WorldMap;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void Init(class APlayor* playor);
	void Refresh();
	void DrawMarker(class UMarkerComponent* nMarker);
	void HideMarker(const class UMarkerComponent* nMarker);
};
