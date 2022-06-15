#include "HudMenu.h"
#include "PlayerMenu.h"
#include "LNR/Body/Avatar.h"
#include "LNR/Widget/HudMenuWidget.h"

AHudMenu::AHudMenu()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHudMenu::DrawHUD()
{
	Super::DrawHUD();
}

void AHudMenu::BeginPlay()
{
	Super::BeginPlay();
	Avatar = Cast<AAvatar>(GetOwningPawn());
	Player = Cast<APlayerMenu>(GetOwningPlayerController());
	if (HudMenuTemplate)
	{
		HudMenuWidget = CreateWidget<UHudMenuWidget>(GetWorld(), HudMenuTemplate);
		if (HudMenuWidget)
		{
			HudMenuWidget->Init(this, Player);
			HudMenuWidget->StartHud();
			HudMenuWidget->AddToViewport();
		}
	}
}
