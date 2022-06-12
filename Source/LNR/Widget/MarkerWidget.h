#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MarkerWidget.generated.h"

UCLASS(Abstract)
class LNR_API UMarkerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class UMarkerComponent* Marker;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UImage* Image;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* Distance;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UProgressBar* ProgressBar;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void Init(UMarkerComponent* nMarker);
	UFUNCTION(BlueprintCallable)
	void Refresh() const;
};