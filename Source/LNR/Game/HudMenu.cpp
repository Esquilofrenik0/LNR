#include "HudMenu.h"
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
	if (HudMenuTemplate)
	{
		HudMenuWidget = CreateWidget<UHudMenuWidget>(GetWorld(), HudMenuTemplate);
		if (HudMenuWidget)
		{
			HudMenuWidget->Init(this);
			HudMenuWidget->AddToViewport();
		}
	}
}
