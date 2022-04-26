#include "EquipmentWidget.h"
#include "Components/Image.h"
#include "LNR/Component/ApparelComponent.h"
#include "LNR/Component/EquipmentComponent.h"
#include "LNR/Item/Armor.h"
#include "LNR/Widget/SlotWidget.h"

void UEquipmentWidget::Refresh(UApparelComponent* apparel, UEquipmentComponent* equipment) const
{
	RefreshArmor(apparel);
	RefreshWeapon(equipment);
}

void UEquipmentWidget::RefreshArmor(UApparelComponent* apparel) const
{
	if (apparel->Armor[0] != nullptr)
	{
		HeadSlot->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		HeadSlot->Image->SetBrushFromTexture(apparel->Armor[0]->Icon);
	}
	else HeadSlot->Image->SetVisibility(ESlateVisibility::Hidden);
	if (apparel->Armor[1] != nullptr)
	{
		BackSlot->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		BackSlot->Image->SetBrushFromTexture(apparel->Armor[1]->Icon);
	}
	else BackSlot->Image->SetVisibility(ESlateVisibility::Hidden);
	if (apparel->Armor[2] != nullptr)
	{
		ChestSlot->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		ChestSlot->Image->SetBrushFromTexture(apparel->Armor[2]->Icon);
	}
	else ChestSlot->Image->SetVisibility(ESlateVisibility::Hidden);
	if (apparel->Armor[3] != nullptr)
	{
		LegsSlot->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		LegsSlot->Image->SetBrushFromTexture(apparel->Armor[3]->Icon);
	}
	else LegsSlot->Image->SetVisibility(ESlateVisibility::Hidden);
	if (apparel->Armor[4] != nullptr)
	{
		FeetSlot->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		FeetSlot->Image->SetBrushFromTexture(apparel->Armor[4]->Icon);
	}
	else FeetSlot->Image->SetVisibility(ESlateVisibility::Hidden);
}

void UEquipmentWidget::RefreshWeapon(UEquipmentComponent* equipment) const
{
	if (equipment->Weapon[0] != nullptr)
	{
		RightHandSlot->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		RightHandSlot->Image->SetBrushFromTexture(equipment->Weapon[0]->Icon);
	}
	else RightHandSlot->Image->SetVisibility(ESlateVisibility::Hidden);
	if (equipment->Weapon[1] != nullptr)
	{
		LeftHandSlot->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		LeftHandSlot->Image->SetBrushFromTexture(equipment->Weapon[1]->Icon);
	}
	else LeftHandSlot->Image->SetVisibility(ESlateVisibility::Hidden);
	if (equipment->Weapon[2] != nullptr)
	{
		RightOffHandSlot->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		RightOffHandSlot->Image->SetBrushFromTexture(equipment->Weapon[2]->Icon);
	}
	else RightOffHandSlot->Image->SetVisibility(ESlateVisibility::Hidden);
	if (equipment->Weapon[3] != nullptr)
	{
		LeftOffHandSlot->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
		LeftOffHandSlot->Image->SetBrushFromTexture(equipment->Weapon[3]->Icon);
	}
	else LeftOffHandSlot->Image->SetVisibility(ESlateVisibility::Hidden);
}
