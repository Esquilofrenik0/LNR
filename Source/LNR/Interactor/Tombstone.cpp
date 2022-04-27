#include "Tombstone.h"
#include "LNR/Body/Hero.h"
#include "LNR/Game/HudBitloner.h"
#include "LNR/Game/Playor.h"

void ATombstone::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().ClearTimer(DestroyHandle);
	GetWorldTimerManager().SetTimer(DestroyHandle, this, &ATombstone::DestroyThis, MaxAliveTime);
}

void ATombstone::OnInteract_Implementation(AHero* nHero)
{
	Hero = nHero;
	Hero->Container = Inventory;
	Hero->Player->Hud->ShowInventory(true);
	GetWorldTimerManager().ClearTimer(DestroyHandle);
	GetWorldTimerManager().ClearTimer(CloseHandle);
	GetWorldTimerManager().SetTimer(CloseHandle, this, &ATombstone::CheckHeroDistance, 0.25f, true);
}

void ATombstone::Close()
{
	Super::Close();
	GetWorldTimerManager().ClearTimer(DestroyHandle);
	GetWorldTimerManager().SetTimer(DestroyHandle, this, &ATombstone::DestroyThis, MaxAliveTime);
}

void ATombstone::DestroyThis()
{
	GetWorldTimerManager().ClearTimer(DestroyHandle);
	Destroy();
}
