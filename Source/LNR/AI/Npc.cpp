#include "Npc.h"
#include "LNR/Body/Body.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LNR/Component/CombatComponent.h"
#include "LNR/Widget/InfoWidget.h"

ANpc::ANpc()
{
	PrimaryActorTick.bCanEverTick = true;
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception")));
	SightConfig->SightRadius = SightRadius;
	SightConfig->LoseSightRadius = LooseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = FieldOfView;
	SightConfig->SetMaxAge(SightAge);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	TargetKey = "Target";
	DestinationKey = "Destination";
}

void ANpc::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);
	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ANpc::OnPawnDetected);
	SpawnPoint = transform.GetLocation();
}

void ANpc::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Body = Cast<ABody>(InPawn);
	BlackboardComponent->InitializeBlackboard(*BlackboardComponent->GetBlackboardAsset());
	BrainComponent->StartLogic();
}

void ANpc::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	if (!Body) Body = Cast<ABody>(GetOwner());
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
