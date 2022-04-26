#include "WeaponComponent.h"

UWeaponComponent::UWeaponComponent()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
}