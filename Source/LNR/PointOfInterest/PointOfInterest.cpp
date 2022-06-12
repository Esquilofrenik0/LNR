#include "PointOfInterest.h"
#include "LNR/Component/MarkerComponent.h"

UPointOfInterest::UPointOfInterest()
{
	Marker = CreateDefaultSubobject<UMarkerComponent>("Marker");
}
