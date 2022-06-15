#pragma once
#include "CoreMinimal.h"
#include "PlayerAvatar.generated.h"

UCLASS()
class LNR_API APlayerAvatar : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class AHudAvatar* Hud;
	UFUNCTION(BlueprintCallable)
	virtual void OnPossess(APawn* InPawn) override;
};
