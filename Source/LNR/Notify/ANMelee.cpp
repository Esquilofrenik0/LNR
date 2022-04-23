#include "ANMelee.h"
#include "LNR/Body/Body.h"
#include "LNR/Component/CombatComponent.h"
#include "LNR/Component/EquipmentComponent.h"

void UANMelee::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	AActor* owner = MeshComp->GetOwner();
	if (owner->HasAuthority()) Body = Cast<ABody>(owner);
}

void UANMelee::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (Body)
	{
		if(Body->Equipment->RightHand != nullptr)
		{
			Body->Combat->TraceWeapon(Body->Equipment->RightHand);
		}
		else
		{
			if (MeleeSockets.IsEmpty()) Body->Combat->TraceMelee();
			else Body->Combat->TraceMeleeSockets(MeleeSockets, MeleeSocketRadius);			
		}
	}
}
