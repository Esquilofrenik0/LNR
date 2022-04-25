#include "BTGetPatrolPoint.h"
#include "LNR/AI/Npc.h"
#include "LNR/Body/Body.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTGetPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(GetWorld()))
	{
		const ANpc* npc = Cast<ANpc>(OwnerComp.GetAIOwner());
		if (FNavLocation result; navSys->GetRandomReachablePointInRadius(npc->SpawnPoint, npc->PatrolDistance, result))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector("Destination", result.Location);
			const ABody* body = Cast<ABody>(npc->GetPawn());
			body->GetCharacterMovement()->MaxWalkSpeed = body->WalkSpeed;
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Set new destination!");
			return EBTNodeResult::Succeeded;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Red, "Couldn't find reachable point!");
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Red, "Couldn't find navigation system!");
		return EBTNodeResult::Failed;
	}
}
