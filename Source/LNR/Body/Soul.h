#pragma once
#include "GameFramework/Character.h"
#include "LNR/Interface/Interact.h"
#include "Soul.generated.h"

UCLASS()
class LNR_API ASoul : public ACharacter, public IInteract
{
	GENERATED_BODY()
public:
	ASoul();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UNavigationInvokerComponent* NavigationInvoker;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UFactionComponent* Faction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UInfoComponent* Info;

	UPROPERTY(BlueprintReadWrite)
	class UBitloner* Bitloner;
	UPROPERTY(BlueprintReadWrite)
	class ANpc* Npc;
	UPROPERTY(BlueprintReadWrite)
	UCapsuleComponent* Capsule;
	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* BodyMesh;
	UPROPERTY(BlueprintReadWrite)
	UCharacterMovementComponent* Movement;
	UPROPERTY(BlueprintReadWrite)
	UAnimInstance* Animator;

	void Init();
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Restart() override;
	virtual void OnInteract_Implementation(AHero* hero) override;
	virtual void OnShowInfo_Implementation(AHero* hero, bool val) override;

	UFUNCTION(BlueprintCallable)
	AActor* SpawnActor(const TSubclassOf<AActor> toSpawn, const FVector location, const FRotator rotation) const;
	UFUNCTION(BlueprintCallable)
	void SetRagdoll(bool value);
	UFUNCTION(Server, Reliable)
	void ServerSetRagdoll(bool value);
	void ServerSetRagdoll_Implementation(bool value) { MultiSetRagdoll(value); }
	UFUNCTION(NetMulticast, Reliable)
	void MultiSetRagdoll(bool value);
};
