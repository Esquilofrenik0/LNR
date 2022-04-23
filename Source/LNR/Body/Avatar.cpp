#include "Avatar.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LNR/Component/ApparelComponent.h"
#include "LNR/Component/AvatarComponent.h"

AAvatar::AAvatar()
{
	PrimaryActorTick.bCanEverTick = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	Apparel = CreateDefaultSubobject<UApparelComponent>("Apparel");
	Apparel->Setup(GetMesh());
	Avatar = CreateDefaultSubobject<UAvatarComponent>("Avatar");
	Avatar->Setup(Apparel);
	TpArm = CreateDefaultSubobject<USpringArmComponent>("TpArm");
	TpArm->SetupAttachment(RootComponent);
	TpArm->TargetArmLength = 200.0f;
	TpArm->bUsePawnControlRotation = true;
	TpCamera = CreateDefaultSubobject<UCameraComponent>("TpCamera");
	TpCamera->SetupAttachment(TpArm, USpringArmComponent::SocketName);
	TpCamera->bUsePawnControlRotation = false;
	TpCamera->SetActive(true);
	TpCamera->SetFieldOfView(90);
}

void AAvatar::BeginPlay()
{
	Super::BeginPlay();
}

void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AAvatar::Zoom);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AAvatar::AddControllerYawInput);
}

void AAvatar::Zoom(float val)
{
	TpArm->TargetArmLength -= val*5;
	if(TpArm->TargetArmLength < 100) TpArm->TargetArmLength = 100;
	if(TpArm->TargetArmLength > 400) TpArm->TargetArmLength = 400;
}
