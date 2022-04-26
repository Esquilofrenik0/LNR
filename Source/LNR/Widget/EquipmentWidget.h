#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentWidget.generated.h"

UCLASS()
class LNR_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
public:
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
	class USlotWidget* RightHandSlot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* LeftHandSlot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* WeaponSwapSlot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* RightOffHandSlot;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class USlotWidget* LeftOffHandSlot;
	void Refresh(class UApparelComponent* apparel, class UEquipmentComponent* equipment) const;
	void RefreshArmor(UApparelComponent* apparel) const;
	void RefreshWeapon(UEquipmentComponent* equipment) const;
};
