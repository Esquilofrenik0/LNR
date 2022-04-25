#include "BTRunAway.h"
#include "LNR/AI/Npc.h"
#include "LNR/Body/Body.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

EBTNodeResult::Type UBTRunAway::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANpc* npc = Cast<ANpc>(OwnerComp.GetAIOwner());
	ABody* body = Cast<ABody>(npc->GetPawn());
	if(npc->UnderAttack) body->GetCharacterMovement()->MaxWalkSpeed = body->SprintSpeed;
	return EBTNodeResult::Succeeded;
}
