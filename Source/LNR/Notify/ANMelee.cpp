#include "ANMelee.h"
#include "LNR/Body/Body.h"
#include "LNR/Body/Humanoid.h"
#include "LNR/Component/CombatComponent.h"
#include "LNR/Component/EquipmentComponent.h"

void UANMelee::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                           const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	AActor* owner = MeshComp->GetOwner();
	if (owner->HasAuthority())
	{
		Body = Cast<ABody>(owner);
		Humanoid = Cast<AHumanoid>(Body);
	}
}

void UANMelee::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
                          const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	if (Body)
	{
		if (Humanoid && Humanoid->Equipment->RightHand != nullptr)
		{
			Humanoid->Combat->TraceWeapon(Humanoid->Equipment->RightHand);
		}
		else
		{
			if (MeleeSockets.IsEmpty()) Body->Combat->TraceMelee();
			else Body->Combat->TraceMeleeSockets(MeleeSockets, MeleeSocketRadius);
		}
	}
}
