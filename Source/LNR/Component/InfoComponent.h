#pragma once
#include "CoreMinimal.h"
#include "LNR/Widget/InfoWidget.h"
#include "Components/WidgetComponent.h"
#include "InfoComponent.generated.h"

UCLASS()
class LNR_API UInfoComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UInfoComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Value = 0.5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name = "Name";
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Icon = nullptr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor Color = FLinearColor(1.0, 1.0, 1.0, 1.0);
	
	UPROPERTY(BlueprintReadWrite)
	UInfoWidget* InfoWidget;
	UPROPERTY(BlueprintReadWrite)
	bool HideInfoTimerActive = false;
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle HideInfoTimer;

	virtual void OnComponentCreated() override;
	void Setup(ACharacter* character);
	void Init();
	void Init(UAttributesComponent* nAttributes);
	UFUNCTION(BlueprintCallable)
	void Show(bool val);
	UFUNCTION(BlueprintCallable)
	void StartTimer(float time);
	UFUNCTION(BlueprintCallable)
	void ClearTimer();
};
