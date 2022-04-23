#include "ANShoot.h"
#include "LNR/Body/Body.h"
#include "LNR/Component/CombatComponent.h"

void UANShoot::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	AActor* owner = MeshComp->GetOwner();
	if (owner->HasAuthority())
	{
		if (ABody* body = Cast<ABody>(owner)) body->Combat->Shoot();
	}
}
