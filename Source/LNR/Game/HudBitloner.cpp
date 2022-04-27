#include "HudBitloner.h"

#include "Playor.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "LNR/Body/Hero.h"
#include "LNR/Widget/ContainerWidget.h"
#include "LNR/Widget/CraftWidget.h"
#include "LNR/Widget/HudWidget.h"
#include "LNR/Widget/InventoryWidget.h"

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
		HudWidget->Init(this);
		HudWidget->AddToViewport();
		ShowInteractionIcon(false);
		ShowInventory(false);
	}
}

void AHudBitloner::ShowInteractionIcon(bool val)
{
	if (val) HudWidget->InteractionImage->SetVisibility(ESlateVisibility::Visible);
	else HudWidget->InteractionImage->SetVisibility(ESlateVisibility::Hidden);
}

void AHudBitloner::ShowInventory(bool val)
{
	if (val)
	{
		Hero->SetInputUi(true);
		HudWidget->InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		if (Hero->Container)
		{
			HudWidget->InventoryWidget->CraftWidget->SetVisibility(ESlateVisibility::Hidden);
			HudWidget->InventoryWidget->ContainerWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			HudWidget->InventoryWidget->ContainerWidget->SetVisibility(ESlateVisibility::Hidden);
			HudWidget->InventoryWidget->CraftWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		Hero->SetInputUi(false);
		HudWidget->InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		Hero->Container = nullptr;
	}
}
