#include "Soul.h"
#include "NavigationInvokerComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LNR/Component/InfoComponent.h"

ASoul::ASoul()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->InitCapsuleSize(35.f, 85.0f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->GravityScale = 1.75f;
	NavigationInvoker = CreateDefaultSubobject<UNavigationInvokerComponent>("Navigation Invoker");
	Info = CreateDefaultSubobject<UInfoComponent>("Info");
	Info->Setup(this);
}

void ASoul::OnInteract_Implementation(AHero* hero)
{
}

void ASoul::OnShowInfo_Implementation(AHero* hero, bool val)
{
	Info->Show(val);
}
