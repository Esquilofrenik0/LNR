#pragma once
#include "GameFramework/HUD.h"
#include "HudBitloner.generated.h"

UCLASS()
class LNR_API AHudBitloner : public AHUD
{
	GENERATED_BODY()
public:
	AHudBitloner();
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite)
	class AHero* Hero;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHudWidget> HudTemplate;
	UPROPERTY(BlueprintReadWrite)
	UHudWidget* HudWidget;
	UFUNCTION(BlueprintCallable)
	void ShowInteractionIcon(bool val);
	UFUNCTION(BlueprintCallable)
	void ShowInventory(bool val);
	UFUNCTION(BlueprintCallable)
	void RefreshInventory();
};
