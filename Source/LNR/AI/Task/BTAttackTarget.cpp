#include "BTAttackTarget.h"
#include "LNR/AI/Npc.h"
#include "LNR/Body/Body.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LNR/Component/CombatComponent.h"

UBTAttackTarget::UBTAttackTarget()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;
}

EBTNodeResult::Type UBTAttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Npc = Cast<ANpc>(OwnerComp.GetAIOwner());
	Body = Npc->Body;
	if (Npc->Target && Body->Combat->State == Idle)
	{
		Attack();
		return EBTNodeResult::InProgress;
	}
	else
	{
		Body->AttackPressed = false;
		return EBTNodeResult::Succeeded;
	}
}

void UBTAttackTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* nodeMemory, float deltaSeconds)
{
	Super::TickTask(OwnerComp, nodeMemory, deltaSeconds);
	if (Npc && Npc->Target)
	{
		const int distance = FVector::Distance(Body->GetActorLocation(), Npc->Target->GetActorLocation());
		if (distance > Body->Combat->MeleeRange) FinishTask(OwnerComp);
	}
	else FinishTask(OwnerComp);
}

void UBTAttackTarget::Attack()
{
	Body->AttackPressed = true;
	Body->Attack();
}

void UBTAttackTarget::FinishTask(UBehaviorTreeComponent& ownerComp)
{
	Body->AttackPressed = false;
	FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
}
