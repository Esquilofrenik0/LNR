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
	UPROPERTY(BlueprintReadWrite)
	class AAvatar* Avatar;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHudAvatarWidget> HudAvatarTemplate;
	UPROPERTY(BlueprintReadWrite)
	UHudAvatarWidget* HudAvatarWidget;
};