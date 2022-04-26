#include "HudBitloner.h"
#include "Blueprint/UserWidget.h"
#include "LNR/Body/Hero.h"
#include "LNR/Widget/HudWidget.h"

AHudBitloner::AHudBitloner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHudBitloner::DrawHUD()
{
	Super::DrawHUD();
}

void AHudBitloner::BeginPlay()
{
	Super::BeginPlay();
	Hero = Cast<AHero>(GetOwningPawn());
	if (HudTemplate)
	{
		HudWidget = CreateWidget<UHudWidget>(GetWorld(), HudTemplate);
		if (HudWidget)
		{
			HudWidget->Init(this);
			HudWidget->AddToViewport();
		}
	}
}

void AHudBitloner::ShowInteractionIcon(bool val)
{
	if(HudWidget) HudWidget->ShowInteractionIcon(val);
}
