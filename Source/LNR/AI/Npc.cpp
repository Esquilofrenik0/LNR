#include "Npc.h"
#include "LNR/Body/Body.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LNR/Body/Human.h"
#include "LNR/Component/AvatarComponent.h"
#include "LNR/Component/CombatComponent.h"
#include "LNR/Widget/InfoWidget.h"

ANpc::ANpc()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
	bStartAILogicOnPossess = true;
	bAttachToPawn = true;
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>("Perception"));
	SightConfig->SightRadius = SightRadius;
	SightConfig->LoseSightRadius = LooseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = FieldOfView;
	SightConfig->SetMaxAge(SightAge);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>("Behavior Tree");
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
	TargetKey = "Target";
	DestinationKey = "Destination";
}

void ANpc::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);
	Body = Cast<ABody>(GetOwner());
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ANpc::OnPawnDetected);
	BlackboardComponent->InitializeBlackboard(*BlackboardComponent->GetBlackboardAsset());
}

void ANpc::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Body = Cast<ABody>(InPawn);
	SpawnPoint = InPawn->GetActorLocation();
}

void ANpc::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Pawn Detected!");
	if (Body)
	{
		for (int i = 0; i < DetectedPawns.Num(); i++)
		{
			if (ABody* body = Cast<ABody>(DetectedPawns[i])) if (TryTarget(body)) return;
		}
	}
}

void ANpc::CanSeeTarget()
{
	TArray<AActor*> SensedActors;
	GetPerceptionComponent()->GetCurrentlyPerceivedActors(GetPerceptionComponent()->GetDominantSense(), SensedActors);
	if (SensedActors.Contains(Target) && Target->Combat->State != Dead) return;
	if (Body) Body->AttackPressed = false;
	Target = nullptr;
	BlackboardComponent->ClearValue(TargetKey);
	BehaviorTree->RestartTree();
	GetWorldTimerManager().ClearTimer(LooseTargetHandle);
}

void ANpc::StartUnderAttack()
{
	UnderAttack = true;
	GetWorldTimerManager().ClearTimer(UnderAttackHandle);
	GetWorldTimerManager().SetTimer(UnderAttackHandle, this, &ANpc::StopUnderAttack, 8);
	BehaviorTree->RestartTree();
}

void ANpc::StopUnderAttack()
{
	UnderAttack = false;
	// if(Body && Body->Plate) Body->Plate->SetVisibility(false);
	GetWorldTimerManager().ClearTimer(UnderAttackHandle);
	BehaviorTree->RestartTree();
}

bool ANpc::TryTarget(ABody* nBody)
{
	if (nBody && nBody->Combat->State != Dead)
	{
		// bool Hostile = Body->Faction.IsHostileTowards(nBody->Faction);
		// if (!Hostile && Body->IsCitizen && nBody->Attributes->Hate >= 20) Hostile = true;
		// if (Hostile)
		// {
		Target = nBody;
		BlackboardComponent->SetValueAsObject(TargetKey, Target);
		GetWorldTimerManager().ClearTimer(LooseTargetHandle);
		GetWorldTimerManager().SetTimer(LooseTargetHandle, this, &ANpc::CanSeeTarget, 4, true);
		Body->GetCharacterMovement()->MaxWalkSpeed = Body->RunSpeed;
		BehaviorTree->RestartTree();
		return true;
		// }
	}
	return false;
}
