#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InfoWidget.generated.h"

UCLASS(Abstract)
class LNR_API UInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class UInfoComponent* Info;
	UPROPERTY(BlueprintReadWrite)
	class UAttributesComponent* Attributes;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UTextBlock* NameText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UImage* IconImage;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UProgressBar* ValueBar;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void Refresh() const;
};
