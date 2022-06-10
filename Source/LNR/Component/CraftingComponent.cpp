#include "CraftingComponent.h"

UCraftingComponent::UCraftingComponent()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
}
