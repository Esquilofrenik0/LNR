#include "MarkerComponent.h"

UMarkerComponent::UMarkerComponent()
{
		SetIsReplicatedByDefault(true);
		PrimaryComponentTick.bCanEverTick = false;
}
