#include "AvatarComponent.h"
#include "ApparelComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/Game/LNRGameMode.h"
#include "Net/UnrealNetwork.h"

UAvatarComponent::UAvatarComponent()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
}

void UAvatarComponent::OnRep_AvatarData(FAvatarData nAvatarData)
{
	RefreshAvatar();
}

void UAvatarComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAvatarComponent, AvatarData, COND_None, REPNOTIFY_Always);
}

void UAvatarComponent::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ALNRGameMode>(UGameplayStatics::GetGameMode(GetOwner()));
	RefreshAvatar();
}

void UAvatarComponent::Setup(UApparelComponent* nApparel)
{
	Apparel = nApparel;
}

void UAvatarComponent::RefreshAvatar()
{
	if (AvatarData.Body == Male) Apparel->Mesh->SetSkeletalMesh(GameMode->HumanData.Body[0]);
	else if (AvatarData.Body == Female) Apparel->Mesh->SetSkeletalMesh(GameMode->HumanData.Body[1]);
	Apparel->HairMesh->SetSkeletalMesh(GameMode->HumanData.Hair[AvatarData.Hair]);
	Apparel->BeardMesh->SetSkeletalMesh(GameMode->HumanData.Beard[AvatarData.Beard]);
	Apparel->SimgloveMesh->SetSkeletalMesh(GameMode->HumanData.Simglove);
}

void UAvatarComponent::SetBodyType(EGender bodyType)
{
	AvatarData.Body = bodyType;
	RefreshAvatar();
}

void UAvatarComponent::NextHair()
{
	AvatarData.Hair += 1;
	AvatarData.Hair %= GameMode->HumanData.Hair.Num();
	SetHair(AvatarData.Hair);
}

void UAvatarComponent::PreviousHair()
{
	AvatarData.Hair -= 1;
	if (AvatarData.Hair < 0) AvatarData.Hair = GameMode->HumanData.Hair.Num() - 1;
	SetHair(AvatarData.Hair);
}

void UAvatarComponent::SetHair(int val)
{
	AvatarData.Hair = val;
	RefreshAvatar();
}

void UAvatarComponent::NextBeard()
{
	AvatarData.Beard += 1;
	AvatarData.Beard %= GameMode->HumanData.Beard.Num();
	SetBeard(AvatarData.Beard);
}

void UAvatarComponent::PreviousBeard()
{
	AvatarData.Beard -= 1;
	if (AvatarData.Beard < 0) AvatarData.Beard = GameMode->HumanData.Beard.Num() - 1;
	SetBeard(AvatarData.Beard);
}

void UAvatarComponent::SetBeard(int val)
{
	AvatarData.Beard = val;
	RefreshAvatar();
}
