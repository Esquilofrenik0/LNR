#include "BTGetPatrolPoint.h"
#include "LNR/AI/Npc.h"
#include "LNR/Body/Body.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTGetPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANpc* npc = Cast<ANpc>(OwnerComp.GetAIOwner());
	ABody* body = Cast<ABody>(npc->GetPawn());
	body->GetCharacterMovement()->MaxWalkSpeed = body->WalkSpeed;
	if (body->PatrolDistance == 0)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("Destination", npc->SpawnPoint);
		return EBTNodeResult::Succeeded;
	}
	else if (UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
	{
		FNavLocation Result;
		if (NavSys->GetRandomReachablePointInRadius(npc->SpawnPoint, body->PatrolDistance, Result))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector("Destination", Result.Location);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
