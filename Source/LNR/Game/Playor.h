#pragma once
#include "CoreMinimal.h"
#include "Playor.generated.h"

UCLASS()
class LNR_API APlayor : public APlayerController
{
	GENERATED_BODY()
public:
	APlayor();
	UPROPERTY(BlueprintReadWrite)
	class AHero* Hero;
	UPROPERTY(BlueprintReadWrite)
	class AHudBitloner* Hud;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UNavigationComponent* Navigation;

	UFUNCTION(BlueprintCallable)
	void Print(FString txt);
};
