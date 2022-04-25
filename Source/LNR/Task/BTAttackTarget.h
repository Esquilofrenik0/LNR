#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BTAttackTarget.generated.h"

UCLASS()
class LNR_API UBTAttackTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTAttackTarget();
	UPROPERTY(BlueprintReadWrite)
	class ANpc* Npc;
	UPROPERTY(BlueprintReadWrite)
	class ABody* Body;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void Attack();
	void FinishTask(UBehaviorTreeComponent& OwnerComp);
};
