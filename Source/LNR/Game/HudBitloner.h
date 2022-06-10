#pragma once
#include "GameFramework/HUD.h"
#include "HudBitloner.generated.h"

UENUM(BlueprintType)
enum EInteractionType
{
	None = 0,
	Inspect = 1,
	Foliage = 2,
};

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
	void ShowInteractionIcon(bool val, TEnumAsByte<EInteractionType> interactionType = None);
	UFUNCTION(BlueprintCallable)
	void ShowInventory(bool val);
};
