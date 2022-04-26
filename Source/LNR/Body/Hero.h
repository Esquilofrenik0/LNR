#pragma once
#include "CoreMinimal.h"
#include "Human.h"
#include "LNR/Game/Playor.h"
#include "Hero.generated.h"

UCLASS()
class LNR_API AHero : public AHuman
{
	GENERATED_BODY()
public:
	AHero();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* TpArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* TpCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* FpCamera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class USpotLightComponent* Flashlight;

	UPROPERTY(BlueprintReadWrite)
	APlayor* Player;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FirstPerson = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool FlashlightActive = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool ReloadHeld;
	UPROPERTY(BlueprintReadWrite)
	bool WeaponSwapHeld;
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle ReloadHeldTimer;
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle WeaponSwapHeldTimer;

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle ClientTickTimer;
	UPROPERTY(BlueprintReadWrite)
	AActor* Inter = nullptr;
	
	virtual void BeginPlay() override;
	virtual void Restart() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;

	void ClientTick();
	void CheckView();
	void ResetCamera();

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
	void StartAttack();
	void StopAttack();
	void StartBlock();
	void StopBlock();
	void StartSprint();
	void StopSprint();
	void StartWeaponSwap();
	void StopWeaponSwap();
	void StartReload();
	void StopReload();
	
	void StartDodge();
	void StartInteract();
	void StartCycleCamera();
	
	void StartHolster();
	void StartFlashlight();


};
