#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/Body/Body.h"
// #include "LNR/Component/AttributesComponent.h"
// #include "LNR/Component/TraceComponent.h"
// #include "LNR/Component/HeadSphereComponent.h"

UGun::UGun()
{
	MaxAmmo = 0;
}

void UGun::Attack(ABody* body, USkeletalMeshComponent* weapon)
{
	Print("Gun Attack Not Implemented!");	
	// if (AController* controller = body->GetController())
	// {
	// 	FVector start;
	// 	FRotator rot;
	// 	controller->GetPlayerViewPoint(start, rot);
	// 	FVector end = start + (rot.Vector() * 5000.0f);
	// 	FHitResult hit = body->Trace->Line(start, end, 1, false);
	// 	TSubclassOf<UDamageType> dt = body->DamageType[Ranged];
	// 	if (AActor* hitActor = hit.GetActor())
	// 	{
	// 		int dmg = body->Attributes->Damage;
	// 		if (Cast<UHeadSphereComponent>(hit.GetComponent()))
	// 		{
	// 			dt = body->DamageType[Melee];
	// 			dmg *= 2;
	// 		}
	// 		UGameplayStatics::ApplyPointDamage(hitActor, dmg, body->GetActorLocation(), hit,
	// 		                                   body->GetController(), body, dt);
	// 	}
	// }
}
