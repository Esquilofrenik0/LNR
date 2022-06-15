#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudMenuWidget.generated.h"

UCLASS(Abstract)
class LNR_API UHudMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class AHudMenu* Hud;
	UPROPERTY(BlueprintReadWrite)
	class APlayerMenu* Player;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHudAvatarWidget> HudAvatarTemplate;
	UPROPERTY(BlueprintReadWrite)
	UHudAvatarWidget* HudAvatarWidget;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UWidgetSwitcher* Switch;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UOverlay* MenuOverlay;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UOverlay* AvatarOverlay;

	void Init(AHudMenu* nHud, APlayerMenu* nPlayer);
	UFUNCTION(BlueprintImplementableEvent)
	void StartHud();
};
