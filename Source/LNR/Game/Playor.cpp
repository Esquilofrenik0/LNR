#include "Playor.h"
#include "HudBitloner.h"
#include "LNR/Component/NavigationComponent.h"
#include "LNR/Widget/HudWidget.h"

APlayor::APlayor()
{
	Navigation = CreateDefaultSubobject<UNavigationComponent>("Navigation");
}

void APlayor::Print(FString txt)
{
	Hud->HudWidget->Print(txt);
}
