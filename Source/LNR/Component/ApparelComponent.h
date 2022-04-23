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
	
	virtual void BeginPlay() override;
	virtual void OnComponentCreated() override;
	void Setup(USkeletalMeshComponent* nMesh);
	void Dress();
	void CreateDynamicMaterial();
	TArray<UMaterialInstanceDynamic*> GetCharacterMaterials();
	void SetMask(UTexture2D* mask);
	UFUNCTION(BlueprintCallable)
	void SetOutfit(UOutfit* nOutfit);
	UFUNCTION(Server, Reliable)
	void ServerSetOutfit(UOutfit* nOutfit);
	void ServerSetOutfit_Implementation(UOutfit* nOutfit) { SetOutfit(nOutfit); }
};
