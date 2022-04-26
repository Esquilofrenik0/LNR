#include "ANShoot.h"
#include "LNR/Body/Body.h"
#include "LNR/Component/CombatComponent.h"

void UANShoot::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                           const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	AActor* owner = MeshComp->GetOwner();
	if (owner->HasAuthority())
	{
		if (ABody* body = Cast<ABody>(owner)) body->Combat->Shoot();
	}
}
