#include "PlayerMenu.h"
#include "HudMenu.h"

void APlayerMenu::BeginPlay()
{
	Super::BeginPlay();	
}

void APlayerMenu::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AHUD* nHud = GetHUD()) Hud = Cast<AHudMenu>(nHud);
}
