#include "Playor.h"
#include "HudBitloner.h"
#include "LNR/Widget/HudWidget.h"

void APlayor::Print(FString txt)
{
	Hud->HudWidget->Print(txt);
}
