#include "Crate.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/InventoryComponent.h"
#include "LNR/Data/Dropable.h"
#include "LNR/Game/HudBitloner.h"
#include "LNR/Game/Playor.h"

void ACrate::GenerateLoot()
{
	if (HasAuthority())
	{
		if (Dropables != nullptr && LootGenerated == false)
		{
			LootGenerated = true;
			for (auto row : Dropables->GetRowMap())
			{
				FString rowName = (row.Key).ToString();
				FDropable* dropable = (FDropable*)row.Value;
				int rand = FMath::RandRange(0, 100);
				if (dropable->Chance >= rand) Inventory->Add(dropable->Item.GetDefaultObject(), dropable->Amount);
			}
		}
	}
	else ServerGenerateLoot();
}

void ACrate::OnInteract_Implementation(AHero* nHero)
{
	GenerateLoot();
	Hero = nHero;
	Hero->Container = Inventory;
	Hero->Player->Hud->ShowInventory(true);
	GetWorldTimerManager().ClearTimer(DestroyHandle);
	GetWorldTimerManager().ClearTimer(CloseHandle);
	GetWorldTimerManager().SetTimer(CloseHandle, this, &ACrate::CheckHeroDistance, 0.25f, true);
}

void ACrate::Close()
{
	Super::Close();
	GetWorldTimerManager().ClearTimer(DestroyHandle);
	GetWorldTimerManager().SetTimer(DestroyHandle, this, &ACrate::DestroyThis, MaxAliveTime);
}

void ACrate::DestroyThis()
{
	GetWorldTimerManager().ClearTimer(DestroyHandle);
	Destroy();
}
