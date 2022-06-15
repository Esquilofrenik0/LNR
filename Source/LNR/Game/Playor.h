#pragma once
#include "CoreMinimal.h"
#include "Playor.generated.h"

UCLASS()
class LNR_API APlayor : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class AHero* Hero;
	UPROPERTY(BlueprintReadWrite)
	class AHudBitloner* Hud;

	UFUNCTION(BlueprintCallable)
	void Print(FString txt);
};
