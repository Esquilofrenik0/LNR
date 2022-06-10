#pragma once
#include "CoreMinimal.h"
#include "CombatComponent.generated.h"

UENUM(BlueprintType)
enum EState
{
	Dead = 0,
	Idle = 1,
	Blocking = 2,
	Attacking = 3,
	Reacting = 4,
	Climbing = 5,
	Swimming = 6,
};

UCLASS()
class LNR_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UCombatComponent();

	UPROPERTY(ReplicatedUsing = OnRep_State, EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EState> State;
	UFUNCTION()
	void OnRep_State(EState nState);

	UPROPERTY(BlueprintReadWrite)
	class ABody* Body;
	UPROPERTY(BlueprintReadWrite)
	class AHumanoid* Humanoid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> UnarmedMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* TakeDamageMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> DodgeMontage;
	UPROPERTY(Replicated, BlueprintReadWrite)
	TArray<AActor*> MeleeHits;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	int Combo = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MeleeRange = 50;
	UPROPERTY(BlueprintReadWrite, Replicated)
	bool Aiming = false;

	UPROPERTY(BlueprintReadWrite)
	FTimerHandle ResetComboHandle;

	void Setup(ABody* nBody);
	void RefreshState();
	void TraceMelee();
	void TraceMeleeSockets(TArray<FName> sockets, int radius);
	void TraceWeapon(class UWeaponComponent* weapon);
	void Shoot();
	UAnimMontage* GetCombatMontage();
	int GetMaxCombo();
	void ResetCombo();

	UFUNCTION(BlueprintCallable)
	void SetState(EState nState);
	UFUNCTION(Server, Reliable)
	void ServerSetState(EState nState);
	void ServerSetState_Implementation(EState nState) { SetState(nState); }
	
	UFUNCTION(BlueprintCallable)
	void SetAiming(bool val);
	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool val);
	void ServerSetAiming_Implementation(bool val) { SetAiming(val); }
};
