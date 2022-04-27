#include "Playor.h"
#include "HudBitloner.h"
#include "LNR/Body/Hero.h"

void APlayor::Init(AHero* nHero)
{
	Hero = nHero;
	if (AHUD* nHud = GetHUD()) Hud = Cast<AHudBitloner>(nHud);
}

void APlayor::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Hero = Cast<AHero>(InPawn);
	Hero->Player = this;
	if (AHUD* nHud = GetHUD()) Hud = Cast<AHudBitloner>(nHud);
}
