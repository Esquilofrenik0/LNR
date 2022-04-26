#include "EquipmentWidget.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/ApparelComponent.h"
#include "LNR/Component/EquipmentComponent.h"
#include "LNR/Item/Armor.h"
#include "LNR/Widget/SlotWidget.h"

void UEquipmentWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	Refresh();
}

void UEquipmentWidget::Init(AHero* nHero)
{
	Hero = nHero;
	WeaponSwapSlot->OnClick.AddDynamic(Hero, &AHero::TryWeaponSwap);
	RightHandSlot->OnClick.AddDynamic(Hero->Equipment, &UEquipmentComponent::UnequipRightHand);
	LeftHandSlot->OnClick.AddDynamic(Hero->Equipment, &UEquipmentComponent::UnequipLeftHand);
	RightOffHandSlot->OnClick.AddDynamic(Hero->Equipment, &UEquipmentComponent::UnequipRightOffHand);
	LeftOffHandSlot->OnClick.AddDynamic(Hero->Equipment, &UEquipmentComponent::UnequipLeftOffHand);
	HeadSlot->OnClick.AddDynamic(Hero->Apparel, &UApparelComponent::UnequipHead);
	BackSlot->OnClick.AddDynamic(Hero->Apparel, &UApparelComponent::UnequipBack);
	ChestSlot->OnClick.AddDynamic(Hero->Apparel, &UApparelComponent::UnequipChest);
	LegsSlot->OnClick.AddDynamic(Hero->Apparel, &UApparelComponent::UnequipLegs);
	FeetSlot->OnClick.AddDynamic(Hero->Apparel, &UApparelComponent::UnequipFeet);
}

void UEquipmentWidget::Refresh() const
{
	RefreshArmor(Hero->Apparel);
	RefreshWeapon(Hero->Equipment);
}

void UEquipmentWidget::RefreshArmor(UApparelComponent* apparel) const
{
	if (apparel->Armor[0] != nullptr) HeadSlot->Setup(apparel->Armor[0]->Icon);
	else HeadSlot->Setup(nullptr);
	if (apparel->Armor[1] != nullptr) BackSlot->Setup(apparel->Armor[1]->Icon);
	else BackSlot->Setup(nullptr);
	if (apparel->Armor[2] != nullptr) ChestSlot->Setup(apparel->Armor[2]->Icon);
	else ChestSlot->Setup(nullptr);
	if (apparel->Armor[3] != nullptr) LegsSlot->Setup(apparel->Armor[3]->Icon);
	else LegsSlot->Setup(nullptr);
	if (apparel->Armor[4] != nullptr) FeetSlot->Setup(apparel->Armor[4]->Icon);
	else FeetSlot->Setup(nullptr);
}

void UEquipmentWidget::RefreshWeapon(UEquipmentComponent* equipment) const
{
	if (equipment->Weapon[0] != nullptr) RightHandSlot->Setup(equipment->Weapon[0]->Icon);
	else RightHandSlot->Setup(nullptr);
	if (equipment->Weapon[1] != nullptr) LeftHandSlot->Setup(equipment->Weapon[1]->Icon);
	else LeftHandSlot->Setup(nullptr);
	if (equipment->Weapon[2] != nullptr) RightOffHandSlot->Setup(equipment->Weapon[2]->Icon);
	else RightOffHandSlot->Setup(nullptr);
	if (equipment->Weapon[3] != nullptr) LeftOffHandSlot->Setup(equipment->Weapon[3]->Icon);
	else LeftOffHandSlot->Setup(nullptr);
}
