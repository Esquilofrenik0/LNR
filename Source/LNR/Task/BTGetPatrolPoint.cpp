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
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
