#include "AvatarComponent.h"
#include "ApparelComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/Game/Bitloner.h"
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
	Bitloner = Cast<UBitloner>(UGameplayStatics::GetGameInstance(this));
	Character = Cast<ACharacter>(GetOwner());
	RefreshAvatar();
}

void UAvatarComponent::Setup(UApparelComponent* nApparel)
{
	Apparel = nApparel;
}

void UAvatarComponent::RefreshAvatar()
{
	if (Bitloner == nullptr) Bitloner = Cast<UBitloner>(UGameplayStatics::GetGameInstance(this));
	Apparel->Mesh->SetSkeletalMesh(Bitloner->AvatarGlobals.Body[AvatarData.Body]);

	if (AvatarData.Body == 0) Character->GetMesh()->SetWorldScale3D(FVector(1, 1, 1));
	else Character->GetMesh()->SetWorldScale3D(FVector(1.05, 1.05, 1.05));

	// Apparel->UnderwearMesh->SetSkeletalMesh(Bitloner->AvatarGlobals.Underwear[AvatarData.Body]);
	Apparel->HairMesh->SetSkeletalMesh(Bitloner->AvatarGlobals.Hair[AvatarData.Hair]);
	Apparel->BeardMesh->SetSkeletalMesh(Bitloner->AvatarGlobals.Beard[AvatarData.Beard]);
	Apparel->SimgloveMesh->SetSkeletalMesh(Bitloner->AvatarGlobals.Simglove);
}

void UAvatarComponent::RandomizeAvatar()
{
	SetBody(FMath::RandRange(0, Bitloner->AvatarGlobals.Body.Num() - 1));
	SetHair(FMath::RandRange(0, Bitloner->AvatarGlobals.Hair.Num() - 1));
	SetBeard(FMath::RandRange(0, Bitloner->AvatarGlobals.Beard.Num() - 1));
}

void UAvatarComponent::RandomizeOutfit()
{
	int r = FMath::RandRange(0, Bitloner->AvatarGlobals.Outfit.Num() - 1);
	UOutfit* outfit = Bitloner->AvatarGlobals.Outfit[r].GetDefaultObject();
	Apparel->SetOutfit(outfit);
}

void UAvatarComponent::NextBody()
{
	AvatarData.Body += 1;
	AvatarData.Body %= Bitloner->AvatarGlobals.Body.Num();
	SetBody(AvatarData.Body);
}

void UAvatarComponent::PreviousBody()
{
	AvatarData.Body -= 1;
	if (AvatarData.Body < 0) AvatarData.Body = Bitloner->AvatarGlobals.Body.Num() - 1;
	SetBody(AvatarData.Body);
}

void UAvatarComponent::SetBody(int val)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		AvatarData.Body = val;
		RefreshAvatar();
	}
	else ServerSetBody(val);
}

void UAvatarComponent::NextHair()
{
	AvatarData.Hair += 1;
	AvatarData.Hair %= Bitloner->AvatarGlobals.Hair.Num();
	SetHair(AvatarData.Hair);
}

void UAvatarComponent::PreviousHair()
{
	AvatarData.Hair -= 1;
	if (AvatarData.Hair < 0) AvatarData.Hair = Bitloner->AvatarGlobals.Hair.Num() - 1;
	SetHair(AvatarData.Hair);
}

void UAvatarComponent::SetHair(int val)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		AvatarData.Hair = val;
		RefreshAvatar();
	}
	else ServerSetHair(val);
}

void UAvatarComponent::NextBeard()
{
	AvatarData.Beard += 1;
	AvatarData.Beard %= Bitloner->AvatarGlobals.Beard.Num();
	SetBeard(AvatarData.Beard);
}

void UAvatarComponent::PreviousBeard()
{
	AvatarData.Beard -= 1;
	if (AvatarData.Beard < 0) AvatarData.Beard = Bitloner->AvatarGlobals.Beard.Num() - 1;
	SetBeard(AvatarData.Beard);
}

void UAvatarComponent::SetBeard(int val)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		AvatarData.Beard = val;
		RefreshAvatar();
	}
	else ServerSetBeard(val);
}
