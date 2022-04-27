#include "AvatarComponent.h"
#include "ApparelComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/Game/BitlonerGameMode.h"
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
	GameMode = Cast<ABitlonerGameMode>(UGameplayStatics::GetGameMode(GetOwner()));
	RefreshAvatar();
}

void UAvatarComponent::Setup(UApparelComponent* nApparel)
{
	Apparel = nApparel;
}

void UAvatarComponent::RefreshAvatar()
{
	if (GameMode)
	{
		Apparel->Mesh->SetSkeletalMesh(GameMode->AvatarGlobals.Body[AvatarData.Body]);
		Apparel->HairMesh->SetSkeletalMesh(GameMode->AvatarGlobals.Hair[AvatarData.Hair]);
		Apparel->BeardMesh->SetSkeletalMesh(GameMode->AvatarGlobals.Beard[AvatarData.Beard]);
		Apparel->SimgloveMesh->SetSkeletalMesh(GameMode->AvatarGlobals.Simglove);
	}
}

void UAvatarComponent::RandomizeAvatar()
{
	if (GameMode)
	{
		SetBody(FMath::RandRange(0, GameMode->AvatarGlobals.Body.Num() - 1));
		SetHair(FMath::RandRange(0, GameMode->AvatarGlobals.Hair.Num() - 1));
		SetBeard(FMath::RandRange(0, GameMode->AvatarGlobals.Beard.Num() - 1));
	}
}

void UAvatarComponent::RandomizeOutfit()
{
	if (GameMode)
	{
		int r = FMath::RandRange(0, GameMode->AvatarGlobals.Outfit.Num() - 1);
		UOutfit* outfit = GameMode->AvatarGlobals.Outfit[r].GetDefaultObject();
		Apparel->SetOutfit(outfit);
	}
}

void UAvatarComponent::NextBody()
{
	AvatarData.Body += 1;
	AvatarData.Body %= GameMode->AvatarGlobals.Body.Num();
	SetBody(AvatarData.Body);
}

void UAvatarComponent::PreviousBody()
{
	AvatarData.Body -= 1;
	if (AvatarData.Body < 0) AvatarData.Body = GameMode->AvatarGlobals.Body.Num() - 1;
	SetBody(AvatarData.Body);
}

void UAvatarComponent::SetBody(int val)
{
	AvatarData.Body = val;
	RefreshAvatar();
}

void UAvatarComponent::NextHair()
{
	AvatarData.Hair += 1;
	AvatarData.Hair %= GameMode->AvatarGlobals.Hair.Num();
	SetHair(AvatarData.Hair);
}

void UAvatarComponent::PreviousHair()
{
	AvatarData.Hair -= 1;
	if (AvatarData.Hair < 0) AvatarData.Hair = GameMode->AvatarGlobals.Hair.Num() - 1;
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
	AvatarData.Beard %= GameMode->AvatarGlobals.Beard.Num();
	SetBeard(AvatarData.Beard);
}

void UAvatarComponent::PreviousBeard()
{
	AvatarData.Beard -= 1;
	if (AvatarData.Beard < 0) AvatarData.Beard = GameMode->AvatarGlobals.Beard.Num() - 1;
	SetBeard(AvatarData.Beard);
}

void UAvatarComponent::SetBeard(int val)
{
	AvatarData.Beard = val;
	RefreshAvatar();
}
