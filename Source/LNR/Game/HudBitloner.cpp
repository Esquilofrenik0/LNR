#include "HudBitloner.h"
#include "Blueprint/UserWidget.h"
#include "LNR/Body/Hero.h"
#include "LNR/Widget/EquipmentWidget.h"
#include "LNR/Widget/HudWidget.h"
#include "LNR/Widget/BagWidget.h"
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
		RefreshInventory();
		HudWidget->InventoryWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else HudWidget->InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
}

void AHudBitloner::RefreshInventory()
{
	HudWidget->InventoryWidget->BagWidget->Refresh(Hero->Inventory);
	HudWidget->InventoryWidget->EquipmentWidget->Refresh(Hero->Apparel, Hero->Equipment);
}
