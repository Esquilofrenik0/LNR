#include "HudAvatar.h"
#include "LNR/Body/Avatar.h"
#include "LNR/Widget/HudAvatarWidget.h"

AHudAvatar::AHudAvatar()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHudAvatar::DrawHUD()
{
	Super::DrawHUD();
}

void AHudAvatar::BeginPlay()
{
	Super::BeginPlay();
	Avatar = Cast<AAvatar>(GetOwningPawn());
	if (HudAvatarTemplate)
	{
		HudAvatarWidget = CreateWidget<UHudAvatarWidget>(GetWorld(), HudAvatarTemplate);
		if (HudAvatarWidget)
		{
			HudAvatarWidget->Init(this);
			HudAvatarWidget->AddToViewport();
		}
	}
}
