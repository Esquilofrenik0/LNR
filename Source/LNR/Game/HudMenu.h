#pragma once
#include "GameFramework/HUD.h"
#include "HudMenu.generated.h"

UCLASS()
class LNR_API AHudMenu : public AHUD
{
	GENERATED_BODY()
public:
	AHudMenu();
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHudMenuWidget> HudMenuTemplate;
	UPROPERTY(BlueprintReadWrite)
	class UHudMenuWidget* HudMenuWidget;
};