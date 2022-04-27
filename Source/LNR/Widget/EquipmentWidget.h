#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentWidget.generated.h"

UCLASS()
class LNR_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class AHero* Hero;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* RightHandSlot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* LeftHandSlot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* WeaponSwapSlot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* RightOffHandSlot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* LeftOffHandSlot;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* HeadSlot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* BackSlot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* ChestSlot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* LegsSlot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* FeetSlot;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* OutfitSlot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* AmmoSlot;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* Consumable1Slot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* Consumable2Slot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* Consumable3Slot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* Consumable4Slot;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void Init(AHero* nHero);
	void Refresh() const;
	void RefreshArmor(class UApparelComponent* apparel) const;
	void RefreshWeapon(class UEquipmentComponent* equipment) const;
};
