#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ApparelComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LNR_API UApparelComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UApparelComponent();

	UPROPERTY(ReplicatedUsing = OnRep_Armor, Instanced, EditAnywhere, BlueprintReadWrite)
	TArray<class UArmor*> Armor;
	UFUNCTION()
	void OnRep_Armor(TArray<UArmor*> nArmor);

	UPROPERTY(ReplicatedUsing = OnRep_Outfit, EditAnywhere, BlueprintReadWrite, Instanced)
	class UOutfit* Outfit;
	UFUNCTION()
	void OnRep_Outfit(UOutfit* nOutfit);

	UPROPERTY(BlueprintReadWrite)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(BlueprintReadWrite)
	class AHero* Hero;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	USkeletalMeshComponent* HeadMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	USkeletalMeshComponent* BackMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	USkeletalMeshComponent* ChestMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	USkeletalMeshComponent* LegsMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	USkeletalMeshComponent* FeetMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	USkeletalMeshComponent* OutfitMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	USkeletalMeshComponent* HairMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	USkeletalMeshComponent* BeardMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	USkeletalMeshComponent* SimgloveMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	USkeletalMeshComponent* UnderwearMesh;

	virtual void BeginPlay() override;
	virtual void OnComponentCreated() override;
	void Setup(USkeletalMeshComponent* nMesh);
	void Dress();
	void CreateDynamicMaterial() const;
	TArray<UMaterialInstanceDynamic*> GetCharacterMaterials() const;
	void SetMask(UTexture2D* mask);
	void SetOutfit(UOutfit* nOutfit);
	UFUNCTION(Server, Reliable)
	void ServerSetOutfit(UOutfit* nOutfit);
	void ServerSetOutfit_Implementation(UOutfit* nOutfit) { SetOutfit(nOutfit); }
	void SetArmor(int slot, UArmor* nArmor);
	UFUNCTION(Server, Reliable)
	void ServerSetArmor(int slot, UArmor* nArmor);
	void ServerSetArmor_Implementation(int slot, UArmor* nArmor) { SetArmor(slot, nArmor); }

	UFUNCTION(BlueprintCallable)
	void EquipArmor(UArmor* nArmor);
	UFUNCTION(BlueprintCallable)
	void UnequipArmor(int slot);
	UFUNCTION(BlueprintCallable)
	void EquipOutfit(UOutfit* nOutfit);
	UFUNCTION(BlueprintCallable)
	void UnequipOutfit();

	UFUNCTION(BlueprintCallable)
	void UnequipHead() { UnequipArmor(0); };
	UFUNCTION(BlueprintCallable)
	void UnequipBack() { UnequipArmor(1); };
	UFUNCTION(BlueprintCallable)
	void UnequipChest() { UnequipArmor(2); };
	UFUNCTION(BlueprintCallable)
	void UnequipLegs() { UnequipArmor(3); };
	UFUNCTION(BlueprintCallable)
	void UnequipFeet() { UnequipArmor(4); };
};
