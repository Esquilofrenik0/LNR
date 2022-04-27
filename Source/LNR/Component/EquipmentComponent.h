#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LNR/Body/Body.h"
#include "LNR/Data/Slot.h"
#include "LNR/Item/Weapon.h"
#include "EquipmentComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LNR_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UEquipmentComponent();

	UPROPERTY(ReplicatedUsing = OnRep_Weapon, EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<UWeapon*> Weapon;
	UFUNCTION()
	void OnRep_Weapon(TArray<UWeapon*> nWeapon);
	
	UPROPERTY(ReplicatedUsing = OnRep_Holster, EditAnywhere, BlueprintReadWrite)
	bool Holster;
	UFUNCTION()
	void OnRep_Holster(bool nHolster);

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	FAmmoSlot AmmoSlot;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	TArray<FConsumableSlot> Consumable;
	
	UPROPERTY(BlueprintReadWrite)
	ABody* Body;
	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(BlueprintReadWrite)
	AHero* Hero;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UWeaponComponent* RightHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UWeaponComponent* LeftHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UWeaponComponent* RightOffHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UWeaponComponent* LeftOffHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UWeaponComponent* RightHolster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UWeaponComponent* LeftHolster;

	UFUNCTION(BlueprintCallable)
	UWeapon* GetWeapon(int index);

	virtual void BeginPlay() override;
	virtual void OnComponentCreated() override;
	void Setup(ABody* nBody);
	UFUNCTION(BlueprintCallable)
	void Dress();
	UFUNCTION(BlueprintCallable)
	void WeaponSwap();
	UFUNCTION(Server, Reliable)
	void ServerWeaponSwap();
	void ServerWeaponSwap_Implementation() { WeaponSwap(); }
	UFUNCTION(BlueprintCallable)
	void SetWeapon(UWeapon* nWeapon, int index);
	UFUNCTION(Server, Reliable)
	void ServerSetWeapon(UWeapon* nWeapon, int index);
	void ServerSetWeapon_Implementation(UWeapon* nWeapon, int index) { SetWeapon(nWeapon, index); }
	UFUNCTION(BlueprintCallable)
	void SetHolster(bool val);
	UFUNCTION(Server, Reliable)
	void ServerSetHolster(bool val);
	void ServerSetHolster_Implementation(bool val) { SetHolster(val); }

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(UWeapon* nWeapon);
	UFUNCTION(BlueprintCallable)
	void UnequipWeapon(int slot);

	UFUNCTION(BlueprintCallable)
	void UnequipRightHand() { UnequipWeapon(0); };
	UFUNCTION(BlueprintCallable)
	void UnequipLeftHand() { UnequipWeapon(1); };
	UFUNCTION(BlueprintCallable)
	void UnequipRightOffHand() { UnequipWeapon(2); };
	UFUNCTION(BlueprintCallable)
	void UnequipLeftOffHand() { UnequipWeapon(3); };
};
