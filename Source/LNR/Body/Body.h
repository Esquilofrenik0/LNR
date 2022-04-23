#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LNR/LNR.h"
#include "Body.generated.h"

UCLASS()
class LNR_API ABody : public ACharacter
{
	GENERATED_BODY()
public:
	ABody();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UActionComponent* Action;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UAttributesComponent* Attributes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UCombatComponent* Combat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UEquipmentComponent* Equipment;

	UPROPERTY(Replicated, BlueprintReadWrite)
	float Pitch;
	UPROPERTY(Replicated, BlueprintReadWrite)
	int MovementDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WalkSpeed = 200;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RunSpeed = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SprintSpeed = 800;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PatrolDistance = 50;
	
	virtual void Restart() override;
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;
	void Attack();
	void Block();
	void Sprint();
	void Dodge();
	void Reload();
	void Action1();
	void Action2();
	void Action3();
	void Action4();
	
	UFUNCTION(BlueprintCallable)
	int UpdateMovementDirection();
	
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
	void PlayMontage(USkeletalMeshComponent* nMesh, UAnimMontage* nMontage);
	UFUNCTION(Server, Reliable)
	void ServerPlayMontage(USkeletalMeshComponent* nMesh, UAnimMontage* nMontage);
	UFUNCTION(NetMulticast, Reliable)
	void MultiPlayMontage(USkeletalMeshComponent* nMesh, UAnimMontage* nMontage);
	void OnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted);

	UFUNCTION(BlueprintCallable)
	void ShowWorldDamage(int amount, EDamageType nDamageType, FVector hitLocation);
	UFUNCTION(Server, Reliable)
	void ServerShowWorldDamage(int amount, EDamageType nDamageType, FVector hitLocation);
	UFUNCTION(NetMulticast, Reliable)
	void MultiShowWorldDamage(int amount, EDamageType nDamageType, FVector hitLocation);
	UFUNCTION(BlueprintImplementableEvent)
	void OnShowWorldDamage(int amount, EDamageType nDamageType, FVector hitLocation);
};
