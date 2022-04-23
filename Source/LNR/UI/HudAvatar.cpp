#include "HudAvatar.h"

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
	// if (HitComboWidgetClass)
	// {
	// 	HitComboWidget = CreateWidget<UHitComboWidget>(GetWorld(), HitComboWidgetClass);
	// 	if (HitComboWidget)
	// 	{
	// 		HitComboWidget->AddToViewport();
	// 	}
	// }
}