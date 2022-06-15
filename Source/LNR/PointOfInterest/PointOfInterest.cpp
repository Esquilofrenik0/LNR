#include "PointOfInterest.h"
#include "LNR/Component/MarkerComponent.h"

UPointOfInterest::UPointOfInterest()
{
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = false;
	Marker = CreateDefaultSubobject<UMarkerComponent>("Marker");
}
