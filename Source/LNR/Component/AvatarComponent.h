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
	class ALNRGameMode* GameMode;
	UPROPERTY(BlueprintReadWrite)
	class UApparelComponent* Apparel;

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void Setup(UApparelComponent* nApparel);
	UFUNCTION(BlueprintCallable)
	void RefreshAvatar();
	UFUNCTION(BlueprintCallable)
	void SetBodyType(EGender bodyType);
	UFUNCTION(BlueprintCallable)
	void NextHair();
	UFUNCTION(BlueprintCallable)
	void PreviousHair();
	UFUNCTION(BlueprintCallable)
	void SetHair(int val);
	UFUNCTION(BlueprintCallable)
	void NextBeard();
	UFUNCTION(BlueprintCallable)
	void PreviousBeard();
	UFUNCTION(BlueprintCallable)
	void SetBeard(int val);
};
