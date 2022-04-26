#include "ApparelComponent.h"

#include "InventoryComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/Body/Hero.h"
#include "LNR/Game/BitlonerGameMode.h"
#include "LNR/Item/Armor.h"
#include "LNR/Item/Outfit.h"
#include "Net/UnrealNetwork.h"

UApparelComponent::UApparelComponent()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
	HeadMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Head");
	BackMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Back");
	ChestMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Chest");
	LegsMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Legs");
	FeetMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Feet");
	OutfitMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Outfit");
	HairMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Hair");
	BeardMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Beard");
	SimgloveMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Simglove");
	Armor = TArray<UArmor*>();
	Armor.Reset();
	for (int i = 0; i < 5; i++) Armor.Add(nullptr);
}

void UApparelComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UApparelComponent, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UApparelComponent, Outfit, COND_None, REPNOTIFY_Always);
}

void UApparelComponent::BeginPlay()
{
	Super::BeginPlay();
	Hero = Cast<AHero>(GetOwner());
	Dress();
}

void UApparelComponent::OnComponentCreated()
{
	Super::OnComponentCreated();
	CreateDynamicMaterial();
	Dress();
}

void UApparelComponent::Setup(USkeletalMeshComponent* nMesh)
{
	Mesh = nMesh;
	HeadMesh->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	HeadMesh->SetMasterPoseComponent(Mesh);
	BackMesh->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	BackMesh->SetMasterPoseComponent(Mesh);
	ChestMesh->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	ChestMesh->SetMasterPoseComponent(Mesh);
	LegsMesh->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	LegsMesh->SetMasterPoseComponent(Mesh);
	FeetMesh->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	FeetMesh->SetMasterPoseComponent(Mesh);
	OutfitMesh->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	OutfitMesh->SetMasterPoseComponent(Mesh);
	HairMesh->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	HairMesh->SetMasterPoseComponent(Mesh);
	BeardMesh->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	BeardMesh->SetMasterPoseComponent(Mesh);
	SimgloveMesh->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	SimgloveMesh->SetMasterPoseComponent(Mesh);
	CreateDynamicMaterial();
}

void UApparelComponent::OnRep_Outfit(UOutfit* nOutfit)
{
	Dress();
}

void UApparelComponent::OnRep_Armor(TArray<UArmor*> nArmor)
{
	Dress();
}

void UApparelComponent::Dress()
{
	if (Outfit)
	{
		HeadMesh->SetSkeletalMesh(nullptr);
		BackMesh->SetSkeletalMesh(nullptr);
		ChestMesh->SetSkeletalMesh(nullptr);
		LegsMesh->SetSkeletalMesh(nullptr);
		FeetMesh->SetSkeletalMesh(nullptr);
		OutfitMesh->SetSkeletalMesh(Outfit->SkeletalMesh);
		SetMask(Outfit->Mask);
	}
	else
	{
		if (Armor[0]) HeadMesh->SetSkeletalMesh(Armor[0]->SkeletalMesh);
		else HeadMesh->SetSkeletalMesh(nullptr);
		if (Armor[1]) BackMesh->SetSkeletalMesh(Armor[1]->SkeletalMesh);
		else BackMesh->SetSkeletalMesh(nullptr);
		if (Armor[2]) ChestMesh->SetSkeletalMesh(Armor[2]->SkeletalMesh);
		else ChestMesh->SetSkeletalMesh(nullptr);
		if (Armor[3]) LegsMesh->SetSkeletalMesh(Armor[3]->SkeletalMesh);
		else LegsMesh->SetSkeletalMesh(nullptr);
		if (Armor[4]) FeetMesh->SetSkeletalMesh(Armor[4]->SkeletalMesh);
		else FeetMesh->SetSkeletalMesh(nullptr);
		OutfitMesh->SetSkeletalMesh(nullptr);
		SetMask(nullptr);
	}
}

void UApparelComponent::CreateDynamicMaterial()
{
	TArray<UMaterialInterface*> meshMats = Mesh->GetMaterials();
	for (int i = 0; i < meshMats.Num(); i++) Mesh->CreateDynamicMaterialInstance(i, meshMats[i]);
}

TArray<UMaterialInstanceDynamic*> UApparelComponent::GetCharacterMaterials()
{
	TArray<UMaterialInstanceDynamic*> toReturn;
	toReturn.Empty();
	TArray<UMaterialInterface*> meshMats = Mesh->GetMaterials();
	for (int i = 0; i < meshMats.Num(); i++)
	{
		if (UMaterialInstanceDynamic* materialInstance = Cast<UMaterialInstanceDynamic>(meshMats[i]))
		{
			toReturn.Add(materialInstance);
		}
	}
	return toReturn;
}

void UApparelComponent::SetMask(UTexture2D* mask)
{
	TArray<UMaterialInstanceDynamic*> meshMats = GetCharacterMaterials();
	if (meshMats.Num() > 0) meshMats[0]->SetTextureParameterValue("Outfit_Mask", mask);
}

void UApparelComponent::SetOutfit(UOutfit* nOutfit)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		Outfit = nOutfit;
		Dress();
	}
	else ServerSetOutfit(nOutfit);
}

void UApparelComponent::SetArmor(int slot, UArmor* nArmor)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		Armor[slot] = nArmor;
		Dress();
	}
	else ServerSetArmor(slot, nArmor);
}

void UApparelComponent::EquipArmor(UArmor* nArmor)
{
	SetArmor(nArmor->Type, nArmor);
}

void UApparelComponent::UnequipArmor(int slot)
{
	if (Hero) Hero->Inventory->Add(Armor[slot]);
	SetArmor(slot, nullptr);
}
