#include "Soul.h"
#include "NavigationInvokerComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/AI/Npc.h"
#include "LNR/Component/FactionComponent.h"
#include "LNR/Component/InfoComponent.h"
#include "LNR/Game/Bitloner.h"

ASoul::ASoul()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->InitCapsuleSize(35.f, 85.0f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	SetReplicatingMovement(true);
	GetCharacterMovement()->SetIsReplicated(true);
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
	Faction = CreateDefaultSubobject<UFactionComponent>("Faction");
	Info = CreateDefaultSubobject<UInfoComponent>("Info");
}

void ASoul::Init()
{
	Bitloner = Cast<UBitloner>(UGameplayStatics::GetGameInstance(this));
	BodyMesh = GetMesh();
	Capsule = GetCapsuleComponent();
	Movement = GetCharacterMovement();
	Animator = BodyMesh->GetAnimInstance();
	Controller = GetController();
	Npc = Cast<ANpc>(Controller);
}

void ASoul::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Info->Setup(this);
}

void ASoul::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ASoul::Restart()
{
	Super::Restart();
	Init();
}

void ASoul::OnInteract_Implementation(AHero* hero)
{
}

void ASoul::OnShowInfo_Implementation(AHero* hero, bool val)
{
	Info->Show(val);
}

void ASoul::SetRagdoll(bool value)
{
	if (HasAuthority()) MultiSetRagdoll(value);
	else ServerSetRagdoll(value);
}

void ASoul::MultiSetRagdoll_Implementation(bool value)
{
	Info->SetHiddenInGame(value);
	BodyMesh->SetSimulatePhysics(value);
	if (value) Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	else Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
