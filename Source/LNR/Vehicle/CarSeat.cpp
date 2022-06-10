#include "CarSeat.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LNR/Body/Hero.h"
#include "Net/UnrealNetwork.h"

UCarSeat::UCarSeat()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
}

void UCarSeat::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UCarSeat, Owner);
	DOREPLIFETIME(UCarSeat, Driver);
	DOREPLIFETIME(UCarSeat, Player);
	DOREPLIFETIME(UCarSeat, DriverAnimBp);
}

void UCarSeat::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<APawn>(GetOwner());
}

void UCarSeat::GetIn(AHero* nHero)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		Driver = nHero;
		Player = Cast<APlayerController>(Driver->GetController());
		USkeletalMeshComponent* mesh = Driver->GetMesh();
		DriverAnimBp = mesh->GetAnimInstance()->GetClass();
		SetupDriver(Driver, true, CarAnimBp);
		Player->Possess(Owner);
	}
	else ServerGetIn(nHero);
}

void UCarSeat::GetOut()
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		SetupDriver(Driver, false, DriverAnimBp);
		const FVector location = Owner->GetActorLocation();
		Driver->SetActorLocation(FVector(location.X, location.Y + ExitDistance, location.Z));
		Player->Possess(Driver);
		Driver = nullptr;
	}
	else ServerGetOut();
}

void UCarSeat::SetupDriver(AHero* nHero, bool gettingIn, TSubclassOf<UAnimInstance> animInstance)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		ExecuteSetupDriver(nHero, gettingIn, animInstance);
		MultiSetupDriver(nHero, gettingIn, animInstance);
	}
	else ServerSetupDriver(nHero, gettingIn, animInstance);
}

void UCarSeat::ServerSetupDriver_Implementation(AHero* nHero, bool gettingIn, TSubclassOf<UAnimInstance> animInstance)
{
	SetupDriver(nHero, gettingIn, animInstance);
}

void UCarSeat::MultiSetupDriver_Implementation(AHero* nHero, bool gettingIn, TSubclassOf<UAnimInstance> animInstance)
{
	ExecuteSetupDriver(nHero, gettingIn, animInstance);
}

void UCarSeat::ExecuteSetupDriver(AHero* nHero, bool gettingIn, TSubclassOf<UAnimInstance> animInstance)
{
	if (gettingIn)
	{
		nHero->SetActorEnableCollision(false);
		nHero->AttachToActor(Owner, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
		nHero->SetActorHiddenInGame(true);
	}
	else
	{
		nHero->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepRelative, false));
		nHero->SetActorEnableCollision(true);
		nHero->SetActorHiddenInGame(false);
	}
	nHero->GetMesh()->SetAnimInstanceClass(animInstance);
}
