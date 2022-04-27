#include "Explosive.h"
#include "XFireBlueprintFunctionLibrary.h"

void AExplosive::BeginPlay()
{
	Super::BeginPlay();
	FireManager = UXFireBlueprintFunctionLibrary::GetXFireManager(this);
}

void AExplosive::Explode(FVector location)
{
	if(HasAuthority()) OnExplode(location);
	else ServerExplode(location);
}

float AExplosive::TakeDamage(float damageAmount, FDamageEvent const& damageEvent, AController* eventInstigator,
                             AActor* damageCauser)
{
	Explode(GetActorLocation());
	return Super::TakeDamage(damageAmount, damageEvent, eventInstigator, damageCauser);
}

void AExplosive::FireDamage_Implementation(UXFireInstance* fireInstance, FXFireSettings fireSettings, float maxDamage,
	float damage)
{
	IXFireInterface::FireDamage_Implementation(fireInstance, fireSettings, maxDamage, damage);
	TakeDamage(damage, FDamageEvent(), nullptr, nullptr);
}
