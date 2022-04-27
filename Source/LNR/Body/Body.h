#pragma once
#include "CoreMinimal.h"
#include "Soul.h"
#include "AbilitySystemInterface.h"
#include "LNR/LNR.h"
#include "LNR/Component/ActionComponent.h"
#include "Body.generated.h"

UCLASS()
class LNR_API ABody : public ASoul, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ABody();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	class UActionComponent* Action;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	class UAttributesComponent* Attributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Instanced)
	class UCombatComponent* Combat;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UDataTable* Dropables;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int WalkSpeed = 200;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int RunSpeed = 500;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int SprintSpeed = 700;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int RespawnTime = 30;

	UPROPERTY(Replicated, BlueprintReadWrite)
	float Pitch;
	UPROPERTY(Replicated, BlueprintReadWrite)
	int MovementDirection;
	UPROPERTY(Replicated, BlueprintReadWrite)
	class ATombstone* Tombstone;
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle RespawnHandle;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return Action; }
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Restart() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;
	void Attack() const;
	void Block() const;
	void Sprint() const;
	void Dodge() const;
	void Reload() const;
	void Action1() const;
	void Action2() const;
	void Action3() const;
	void Action4() const;

	UFUNCTION(BlueprintCallable)
	int UpdateMovementDirection();
	UFUNCTION(BlueprintCallable)
	void RefreshPitch();
	UFUNCTION(BlueprintCallable)
	virtual void RefreshAttributes();

	UFUNCTION(BlueprintCallable)
	virtual void Die();
	UFUNCTION(BlueprintCallable)
	virtual void DestroyCorpse();

	UPROPERTY(Replicated, BlueprintReadWrite)
	bool AttackPressed;
	UFUNCTION(BlueprintCallable)
	void SetAttackPressed(bool val);
	UFUNCTION(Server, Reliable)
	void ServerSetAttackPressed(bool val);
	void ServerSetAttackPressed_Implementation(bool val) { SetAttackPressed(val); }
	UPROPERTY(Replicated, BlueprintReadWrite)
	bool BlockPressed;
	UFUNCTION(BlueprintCallable)
	void SetBlockPressed(bool val);
	UFUNCTION(Server, Reliable)
	void ServerSetBlockPressed(bool val);
	void ServerSetBlockPressed_Implementation(bool val) { SetBlockPressed(val); }
	UPROPERTY(Replicated, BlueprintReadWrite)
	bool SprintPressed;
	UFUNCTION(BlueprintCallable)
	void SetSprintPressed(bool val);
	UFUNCTION(Server, Reliable)
	void ServerSetSprintPressed(bool val);
	void ServerSetSprintPressed_Implementation(bool val) { SetSprintPressed(val); }

	UFUNCTION(BlueprintCallable)
	void PlayMontage(UAnimMontage* nMontage);
	UFUNCTION(Server, Reliable)
	void ServerPlayMontage(UAnimMontage* nMontage);
	void ServerPlayMontage_Implementation(UAnimMontage* nMontage) { PlayMontage(nMontage); }
	UFUNCTION(NetMulticast, Reliable)
	void MultiPlayMontage(UAnimMontage* nMontage);
	void OnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted);

	UFUNCTION(BlueprintCallable)
	void ShowWorldDamage(int amount, EDamageType nDamageType, FVector hitLocation);
	UFUNCTION(Server, Reliable)
	void ServerShowWorldDamage(int amount, EDamageType nDamageType, FVector hitLocation);
	UFUNCTION(NetMulticast, Reliable)
	void MultiShowWorldDamage(int amount, EDamageType nDamageType, FVector hitLocation);
	UFUNCTION(BlueprintImplementableEvent)
	void OnShowWorldDamage(int amount, EDamageType nDamageType, FVector hitLocation);

	UFUNCTION(BlueprintCallable)
	void DropTombstone();
	UFUNCTION(Server, Reliable)
	void ServerDropTombstone();
	void ServerDropTombstone_Implementation() { DropTombstone(); }
	virtual void ExecuteDropTombstone();
};
