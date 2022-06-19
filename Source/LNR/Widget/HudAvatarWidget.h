#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LNR/Data/AvatarData.h"
#include "HudAvatarWidget.generated.h"

UCLASS(Abstract)
class LNR_API UHudAvatarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class AHudMenu* Hud;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FMorphPageData> MorphPageData;
	void Init(AHudMenu* nHud);
};
