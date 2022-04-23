#pragma once
#include "GameFramework/HUD.h"
#include "HudAvatar.generated.h"

UCLASS()
class LNR_API AHudAvatar : public AHUD
{
	GENERATED_BODY()
public:
	AHudAvatar();
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	// UPROPERTY(EditDefaultsOnly, Category = "Interactive")
	// TSubclassOf<UUserWidget> HitComboWidgetClass;
// private:
	// UHitComboWidget* HitComboWidget;
};