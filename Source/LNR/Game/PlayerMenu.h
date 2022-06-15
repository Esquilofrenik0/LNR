#pragma once
#include "CoreMinimal.h"
#include "PlayerMenu.generated.h"

UCLASS()
class LNR_API APlayerMenu : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class AHudMenu* Hud;
	UFUNCTION(BlueprintCallable)
	virtual void OnPossess(APawn* InPawn) override;
};
