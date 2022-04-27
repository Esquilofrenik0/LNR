#include "Container.h"
#include "Kismet/KismetMathLibrary.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/InventoryComponent.h"
#include "LNR/Game/HudBitloner.h"
#include "LNR/Game/Playor.h"
#include "LNR/Widget/InfoWidget.h"

AContainer::AContainer()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
}

FString AContainer::PrintContainerData()
{
	FString data;
	data = GetName();
	data += "\rSlots: " + FString::FromInt(Inventory->Slots.Num());
	return data;
}

void AContainer::OnInteract_Implementation(AHero* nHero)
{
	Hero = nHero;
	Hero->Container = Inventory;
	Hero->Player->Hud->ShowInventory(true);
	GetWorldTimerManager().ClearTimer(CloseHandle);
	GetWorldTimerManager().SetTimer(CloseHandle, this, &AContainer::CheckHeroDistance, 0.25f, true);
}

void AContainer::CheckHeroDistance()
{
	float dist = UKismetMathLibrary::Vector_Distance(GetActorLocation(), Hero->GetActorLocation());
	if (dist > 500) Close();
}

void AContainer::Close()
{
	GetWorldTimerManager().ClearTimer(CloseHandle);
	if (Hero)
	{
		Hero->Container = nullptr;
		Hero->Player->Hud->ShowInventory(false);
		Hero = nullptr;
	}
}
