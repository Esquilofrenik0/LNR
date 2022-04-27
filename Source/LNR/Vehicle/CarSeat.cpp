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
		SetupDriver(Driver, false, CarAnimBp);
		Driver->AttachToActor(Owner, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
		Player->Possess(Owner);
	}
	else ServerGetIn(nHero);
}

void UCarSeat::GetOut()
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		Driver->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepRelative, false));
		SetupDriver(Driver, true, DriverAnimBp);
		FVector location = Owner->GetActorLocation();
		Driver->SetActorLocation(FVector(location.X, location.Y + ExitDistance, location.Z));
		Player->Possess(Driver);
	}
	else ServerGetOut();
}

void UCarSeat::SetupDriver(AHero* nHero, bool collision, TSubclassOf<UAnimInstance> animInstance)
{
	if(GetOwnerRole() == ROLE_Authority) MultiSetupDriver(nHero, collision, animInstance);
	else ServerSetupDriver(nHero, collision, animInstance);
}

void UCarSeat::ServerSetupDriver_Implementation(AHero* nHero, bool collision, TSubclassOf<UAnimInstance> animInstance)
{
	MultiSetupDriver(nHero, collision, animInstance);
}

void UCarSeat::MultiSetupDriver_Implementation(AHero* nHero, bool collision, TSubclassOf<UAnimInstance> animInstance)
{
	nHero->SetActorEnableCollision(collision);
	if(collision) nHero->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	else nHero->GetCharacterMovement()->SetMovementMode(MOVE_None);
	nHero->GetMesh()->SetAnimInstanceClass(animInstance);
}
