#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CarSeat.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LNR_API UCarSeat : public UActorComponent
{
	GENERATED_BODY()
public:
	UCarSeat();
	UPROPERTY(Replicated, BlueprintReadWrite)
	class APawn* Owner;
	UPROPERTY(Replicated, BlueprintReadWrite)
	class AHero* Driver;
	UPROPERTY(Replicated, BlueprintReadWrite)
	class APlayerController* Player;
	UPROPERTY(Replicated, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> DriverAnimBp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> CarAnimBp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ExitDistance = 100;

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void GetIn(class AHero* nHero);
	UFUNCTION(Server, Reliable)
	void ServerGetIn(AHero* nHero);
	void ServerGetIn_Implementation(AHero* nHero) { GetIn(nHero); }
	UFUNCTION(BlueprintCallable)
	void GetOut();
	UFUNCTION(Server, Reliable)
	void ServerGetOut();
	void ServerGetOut_Implementation() { GetOut(); }

	UFUNCTION(BlueprintCallable)
	void SetupDriver(AHero* nHero, bool collision, TSubclassOf<UAnimInstance> animInstance);
	UFUNCTION(Server, Reliable)
	void ServerSetupDriver(AHero* nHero, bool collision, TSubclassOf<UAnimInstance> animInstance);
	UFUNCTION(NetMulticast, Reliable)
	void MultiSetupDriver(AHero* nHero, bool collision, TSubclassOf<UAnimInstance> animInstance);
};
