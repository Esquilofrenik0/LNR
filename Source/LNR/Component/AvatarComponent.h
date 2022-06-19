#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LNR/Data/AvatarData.h"
#include "AvatarComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LNR_API UAvatarComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UAvatarComponent();

	UPROPERTY(ReplicatedUsing = OnRep_AvatarData, EditAnywhere, BlueprintReadWrite)
	FAvatarData AvatarData;
	UFUNCTION()
	void OnRep_AvatarData(FAvatarData nAvatarData);

	UPROPERTY(BlueprintReadWrite)
	class UBitloner* Bitloner;
	UPROPERTY(BlueprintReadWrite)
    class ACharacter* Character;
	UPROPERTY(BlueprintReadWrite)
	class UApparelComponent* Apparel;

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void Setup(UApparelComponent* nApparel);
	UFUNCTION(BlueprintCallable)
	void RefreshAvatar();
	UFUNCTION(BlueprintCallable)
	void RandomizeAvatar();
	UFUNCTION(BlueprintCallable)
	void RandomizeOutfit();

	UFUNCTION(BlueprintCallable)
	void NextBody();
	UFUNCTION(BlueprintCallable)
	void PreviousBody();
	UFUNCTION(BlueprintCallable)
	void SetBody(int val);
	UFUNCTION(Server, Reliable)
	void ServerSetBody(int val);
	void ServerSetBody_Implementation(int val) { SetBody(val); }

	UFUNCTION(BlueprintCallable)
	void NextHair();
	UFUNCTION(BlueprintCallable)
	void PreviousHair();
	UFUNCTION(BlueprintCallable)
	void SetHair(int val);
	UFUNCTION(Server, Reliable)
	void ServerSetHair(int val);
	void ServerSetHair_Implementation(int val) { SetHair(val); }

	UFUNCTION(BlueprintCallable)
	void NextBeard();
	UFUNCTION(BlueprintCallable)
	void PreviousBeard();
	UFUNCTION(BlueprintCallable)
	void SetBeard(int val);
	UFUNCTION(Server, Reliable)
	void ServerSetBeard(int val);
	void ServerSetBeard_Implementation(int val) { SetBeard(val); }
};
