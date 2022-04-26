#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributesWidget.generated.h"

UCLASS()
class LNR_API UAttributesWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class UAttributesComponent* Attributes;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UProgressBar* HealthBar;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UProgressBar* StaminaBar;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UProgressBar* EnergyBar;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UProgressBar* WantedBar;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
