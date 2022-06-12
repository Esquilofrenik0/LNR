#include "ControlPoint.h"
#include "LNR/Body/Body.h"
#include "LNR/Component/CombatComponent.h"
#include "LNR/Component/MarkerComponent.h"
#include "LNR/Game/Bitloner.h"

UControlPoint::UControlPoint()
{
	Influence = 1;
	IncrementAmount = 0.01;
	Marker->ControlPoint = this;
}

void UControlPoint::AddBody(ABody* body)
{
	Bodies.Add(body);
	ContestingFaction = GetWinningFaction();
	if (Faction->Faction == ContestingFaction)
	{
		if (Influence < 1) StartIncreaseInfluence();
	}
	else StartDecreaseInfluence();
}

void UControlPoint::RemoveBody(ABody* body)
{
	Bodies.Remove(body);
	ContestingFaction = GetWinningFaction();
	if (Faction->Faction == ContestingFaction)
	{
		if (Influence < 1) StartIncreaseInfluence();
	}
	else StartDecreaseInfluence();
}

void UControlPoint::StartIncreaseInfluence()
{
	GetWorld()->GetTimerManager().ClearTimer(InfluenceTimer);
	GetWorld()->GetTimerManager().SetTimer(InfluenceTimer, this, &UControlPoint::IncreaseInfluence, 0.1f, true);
}

void UControlPoint::IncreaseInfluence()
{
	Influence += IncrementAmount;
	if (Influence >= 1)
	{
		Influence = 1;
		ContestingFaction = Faction->Faction;
		GetWorld()->GetTimerManager().ClearTimer(InfluenceTimer);
	}
}

void UControlPoint::StartDecreaseInfluence()
{
	GetWorld()->GetTimerManager().ClearTimer(InfluenceTimer);
	GetWorld()->GetTimerManager().SetTimer(InfluenceTimer, this, &UControlPoint::DecreaseInfluence, 0.1f, true);
}

void UControlPoint::DecreaseInfluence()
{
	Influence -= IncrementAmount;
	if (Influence <= 0)
	{
		Influence = 0;
		Faction->Faction = ContestingFaction;
		Marker->Icon = Faction->GetFactionIcon();
		Marker->Color = Faction->GetFactionColor();
		SetControl.Broadcast();
		GetWorld()->GetTimerManager().ClearTimer(InfluenceTimer);
		GetWorld()->GetTimerManager().SetTimer(InfluenceTimer, this, &UControlPoint::IncreaseInfluence, 0.1f, true);
	}
}

EFaction UControlPoint::GetWinningFaction()
{
	TArray<int> FactionPoints;
	FactionPoints.Init(0, Faction->Bitloner->FactionGlobals.Faction.Num());
	int i = 0;
	for (ABody* body : Bodies)
	{
		if (body->Combat->State != Dead) FactionPoints[body->Faction->Faction] += 1;
		i++;
	}
	if (i == 0 || (i == 1 && Bodies[0]->Faction->Faction == Faction->Faction)) return Faction->Faction;

	int winningScore = FactionPoints[Faction->Faction];
	EFaction winningFaction = Faction->Faction;
	int j;
	for (j = 0; j < FactionPoints.Num(); j++)
	{
		if (FactionPoints[j] > winningScore)
		{
			winningScore = FactionPoints[j];
			winningFaction = Faction->Bitloner->FactionGlobals.Faction[j].Faction;
		}
	}
	return winningFaction;
}
