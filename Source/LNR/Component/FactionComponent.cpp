#include "FactionComponent.h"
#include "LNR/Game/Bitloner.h"
#include "Kismet/GameplayStatics.h"

UFactionComponent::UFactionComponent()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
}

void UFactionComponent::BeginPlay()
{
	Super::BeginPlay();
	Bitloner = Cast<UBitloner>(UGameplayStatics::GetGameInstance(this));
}

bool UFactionComponent::CheckCitizenship(EFaction nFaction)
{
	if (nFaction == Empire || nFaction == Survivor || nFaction == Biohacker || nFaction == Inquisitor) return true;
	else return false;
}

bool UFactionComponent::IsCitizen()
{
	return CheckCitizenship(Faction);
}

bool UFactionComponent::IsHostile(EFaction enemy)
{
	switch (Faction)
	{
	case Empire:
		if (CheckCitizenship(enemy)) return false;
		else return true;
	case Survivor:
		if (enemy == Empire || enemy == Survivor || enemy == Critter) return false;
		else return true;
	case Biohacker:
		if (enemy == Empire || enemy == Biohacker || enemy == Critter) return false;
		else return true;
	case Inquisitor:
		if (enemy == Empire || enemy == Inquisitor || enemy == Critter) return false;
		else return true;
	case Mutant:
		if (enemy == Mutant) return false;
		else return true;
	case Rogue:
		if (enemy == Rogue) return false;
		else return true;
	case Feral:
		if (enemy == Feral) return false;
		else return true;
	case Critter: return false;
	default: return false;
	}
}

UTexture2D* UFactionComponent::GetFactionIcon() const
{
	return Bitloner->FactionGlobals.Faction[Faction].Icon;
}

FLinearColor UFactionComponent::GetFactionColor() const
{
	return Bitloner->FactionGlobals.Faction[Faction].Color;
}

TSubclassOf<USpawnData> UFactionComponent::GetFactionSpawnData() const
{
	return Bitloner->FactionGlobals.Faction[Faction].SpawnData;
}
