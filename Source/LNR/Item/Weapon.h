#pragma once
#include "CoreMinimal.h"
#include "Item.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum EWeaponType
{
	Unarmed = 0 UMETA(DisplayName = "Unarmed"),
	Pistol = 1 UMETA(DisplayName = "Pistol"),
	Rifle = 2 UMETA(DisplayName = "Rifle"),
	Jian = 3 UMETA(DisplayName = "Jian"),
	Axe = 4 UMETA(DisplayName = "Axe"),
	Sword = 5 UMETA(DisplayName = "Sword"),
	GreatAxe = 6 UMETA(DisplayName = "GreatAxe"),
	Bow = 7 UMETA(DisplayName = "Bow"),
	Shield = 8 UMETA(DisplayName = "Shield")
};

UENUM(BlueprintType)
enum EWeaponSlot
{
	RightHand = 0 UMETA(DisplayName = "RightHand"),
	LeftHand = 1 UMETA(DisplayName = "LeftHand"),
	TwoHand = 2 UMETA(DisplayName = "TwoHand"),
	AnyHand = 3 UMETA(DisplayName = "AnyHand")
};

UCLASS(Abstract)
class LNR_API UWeapon : public UItem
{
	GENERATED_BODY()
public:
	UWeapon();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMesh* SkeletalMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EWeaponType> Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EWeaponSlot> Slot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> CombatMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* Sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> Attachments;
	
	virtual void UseItem(AHero* hero, int amount) override;
	virtual FString PrintItemData(bool withDescription) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void Attack(class ABody* body, class USkeletalMeshComponent* weapon);
};
