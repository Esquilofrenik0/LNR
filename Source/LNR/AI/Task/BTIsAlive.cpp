#include "BTIsAlive.h"
#include "LNR/AI/Npc.h"
#include "LNR/Body/Body.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "LNR/Component/CombatComponent.h"

EBTNodeResult::Type UBTIsAlive::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ANpc* npc = Cast<ANpc>(OwnerComp.GetAIOwner()))
	{
		if (ABody* body = Cast<ABody>(npc->GetPawn()))
		{
			if (body->Combat->State != Dead) return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
