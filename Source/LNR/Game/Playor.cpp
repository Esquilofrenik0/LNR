#include "Playor.h"
#include "HudBitloner.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "LNR/Widget/HudWidget.h"

void APlayor::BeginPlay()
{
	Super::BeginPlay();
	if (IsLocalController())
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(this);
		SetShowMouseCursor(false);
	}
}

void APlayor::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AHUD* nHud = GetHUD()) Hud = Cast<AHudBitloner>(nHud);
}

void APlayor::Print(FString txt)
{
	Hud->HudWidget->Print(txt);
}
