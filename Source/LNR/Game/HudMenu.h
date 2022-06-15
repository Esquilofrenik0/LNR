#pragma once
#include "GameFramework/HUD.h"
#include "HudMenu.generated.h"

UCLASS()
class LNR_API AHudMenu : public AHUD
{
	GENERATED_BODY()
public:
	AHudMenu();
	UPROPERTY(BlueprintReadWrite)
	class AAvatar* Avatar;
	UPROPERTY(BlueprintReadWrite)
	class APlayerMenu* Player;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHudMenuWidget> HudMenuTemplate;
	UPROPERTY(BlueprintReadWrite)
	UHudMenuWidget* HudMenuWidget;

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
};
