#include "EquipmentComponent.h"
#include "CombatComponent.h"
#include "InventoryComponent.h"
#include "WeaponComponent.h"
#include "GameFramework/Character.h"
#include "LNR/Body/Body.h"
#include "LNR/Body/Hero.h"
#include "LNR/Item/Weapon.h"
#include "Net/UnrealNetwork.h"

UEquipmentComponent::UEquipmentComponent()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
	Holster = true;
	RightHand = CreateDefaultSubobject<UWeaponComponent>("RightHand");
	LeftHand = CreateDefaultSubobject<UWeaponComponent>("LeftHand");
	RightOffHand = CreateDefaultSubobject<UWeaponComponent>("RightOffHand");
	LeftOffHand = CreateDefaultSubobject<UWeaponComponent>("LeftOffHand");
	RightHolster = CreateDefaultSubobject<UWeaponComponent>("RightHolster");
	LeftHolster = CreateDefaultSubobject<UWeaponComponent>("LeftHolster");
	Weapon.Init(nullptr, 4);
	Consumable.Init(FConsumableSlot(), 4);
}

void UEquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UEquipmentComponent, AmmoSlot);
	DOREPLIFETIME(UEquipmentComponent, Consumable);
	DOREPLIFETIME_CONDITION_NOTIFY(UEquipmentComponent, Weapon, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEquipmentComponent, Holster, COND_None, REPNOTIFY_Always);
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	Hero = Cast<AHero>(GetOwner());
	Dress();
}

void UEquipmentComponent::OnComponentCreated()
{
	Super::OnComponentCreated();
	Dress();
}

void UEquipmentComponent::Setup(ABody* nBody)
{
	Body = nBody;
	Mesh = Body->GetMesh();
	RightHand->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, "RightHand");
	LeftHand->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, "LeftHand");
	RightOffHand->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, "RightOffHand");
	LeftOffHand->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, "LeftOffHand");
	RightHolster->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, "RightHolster");
	LeftHolster->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, "LeftHolster");
	Dress();
}

void UEquipmentComponent::OnRep_Weapon(TArray<UWeapon*> nWeapon)
{
	Dress();
}

UWeapon* UEquipmentComponent::GetWeapon(int index)
{
	return Weapon[index];
}

void UEquipmentComponent::OnRep_Holster(bool nHolster)
{
	Dress();
}

void UEquipmentComponent::Dress()
{
	if (Holster)
	{
		RightHand->SetSkeletalMesh(nullptr);
		LeftHand->SetSkeletalMesh(nullptr);
		if (Weapon[0] != nullptr) RightHolster->SetSkeletalMesh(Weapon[0]->SkeletalMesh);
		else RightHolster->SetSkeletalMesh(nullptr);
		if (Weapon[1] != nullptr) LeftHolster->SetSkeletalMesh(Weapon[1]->SkeletalMesh);
		else LeftHolster->SetSkeletalMesh(nullptr);
	}
	else
	{
		RightHolster->SetSkeletalMesh(nullptr);
		LeftHolster->SetSkeletalMesh(nullptr);
		if (Weapon[0] != nullptr) RightHand->SetSkeletalMesh(Weapon[0]->SkeletalMesh);
		else RightHand->SetSkeletalMesh(nullptr);
		if (Weapon[1] != nullptr) LeftHand->SetSkeletalMesh(Weapon[1]->SkeletalMesh);
		else LeftHand->SetSkeletalMesh(nullptr);
	}
	if (Weapon[2] != nullptr) RightOffHand->SetSkeletalMesh(Weapon[2]->SkeletalMesh);
	else RightOffHand->SetSkeletalMesh(nullptr);
	if (Weapon[3] != nullptr) LeftOffHand->SetSkeletalMesh(Weapon[3]->SkeletalMesh);
	else LeftOffHand->SetSkeletalMesh(nullptr);
}

void UEquipmentComponent::SetWeapon(UWeapon* nWeapon, int index)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		Weapon[index] = nWeapon;
		Body->RefreshAttributes();
		Dress();
	}
	else ServerSetWeapon(nWeapon, index);
}

void UEquipmentComponent::SetHolster(bool val)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		Holster = val;
		Dress();
	}
	else ServerSetHolster(val);
}

void UEquipmentComponent::EquipWeapon(UWeapon* nWeapon)
{
	int slot = 0;
	switch (nWeapon->Slot)
	{
	case EWeaponSlot::RightHand:
		slot = 0;
		if (Weapon[0] != nullptr) UnequipWeapon(0);
		break;
	case EWeaponSlot::AnyHand:
		slot = 0;
		if (Weapon[0] != nullptr) UnequipWeapon(0);
		break;
	case EWeaponSlot::LeftHand:
		slot = 1;
		if (Weapon[1] != nullptr)
		{
			if (Weapon[0] != nullptr && Weapon[0]->Type == TwoHand) UnequipWeapon(0);
			UnequipWeapon(1);
		}
		break;
	case EWeaponSlot::TwoHand:
		slot = 0;
		if (Weapon[0] != nullptr) UnequipWeapon(0);
		if (Weapon[1] != nullptr) UnequipWeapon(1);
		break;
	default: break;
	}
	SetWeapon(nWeapon, slot);
}

void UEquipmentComponent::UnequipWeapon(int slot)
{
	if (Hero)
	{
		if (Hero->Inventory->Add(Weapon[slot])) SetWeapon(nullptr, slot);
	}
	else SetWeapon(nullptr, slot);
}

void UEquipmentComponent::WeaponSwap()
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		TArray<UWeapon*> nWeapon;
		nWeapon.Init(nullptr, 4);
		nWeapon[0] = Weapon[2];
		nWeapon[1] = Weapon[3];
		nWeapon[2] = Weapon[0];
		nWeapon[3] = Weapon[1];
		Weapon = nWeapon;
		ResetLoadedAmmo();
		Body->Combat->Combo = 0;
		Body->RefreshAttributes();
		Dress();
	}
	else ServerWeaponSwap();
}

void UEquipmentComponent::SetAmmo(UAmmo* nAmmo, int amount)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		AmmoSlot.Ammo = nAmmo;
		AmmoSlot.Amount = amount;
		AmmoSlot.Loaded = 0;
	}
	else ServerSetAmmo(nAmmo, amount);
}

void UEquipmentComponent::EquipAmmo(UAmmo* nAmmo, int amount)
{
	UnequipAmmo();
	SetAmmo(nAmmo, amount);
}

void UEquipmentComponent::UnequipAmmo()
{
	if (Hero)
	{
		if (Hero->Inventory->Add(AmmoSlot.Ammo, AmmoSlot.Amount + AmmoSlot.Loaded)) SetAmmo(nullptr, 0);
	}
	else SetAmmo(nullptr, 0);
}

void UEquipmentComponent::ResetLoadedAmmo()
{
	AmmoSlot.Amount += AmmoSlot.Loaded;
	AmmoSlot.Loaded = 0;
}

void UEquipmentComponent::SetConsumable(UConsumable* nConsumable, int amount, int index)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		Consumable[index].Consumable = nConsumable;
		Consumable[index].Amount = amount;
	}
	else ServerSetConsumable(nConsumable, amount, index);
}

void UEquipmentComponent::EquipConsumable(UConsumable* nConsumable, int amount, int index)
{
	if (index == -1)
	{
		index = 0;
		for (int i = 0; i < Consumable.Num(); i++)
		{
			if (Consumable[i].Consumable == nullptr)
			{
				index = i;
				break;
			}
		}
	}
	UnequipConsumable(index);
	SetConsumable(nConsumable, amount, index);
}

void UEquipmentComponent::UnequipConsumable(int index)
{
	if (Hero && Consumable[index].Amount > 0 && Consumable[index].Consumable != nullptr)
	{
		Hero->Inventory->Add(Consumable[index].Consumable, Consumable[index].Amount);
	}
	Consumable[index].Amount = 0;
	Consumable[index].Consumable = nullptr;
}
