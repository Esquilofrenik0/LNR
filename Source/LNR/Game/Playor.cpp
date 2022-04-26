#include "Playor.h"
#include "HudBitloner.h"

void APlayor::Init(AHero* nHero)
{
	Hero = nHero;
	Hud = Cast<AHudBitloner>(GetHUD());
}
