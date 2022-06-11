#include "FactionPoint.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/Game/Bitloner.h"

UFactionPoint::UFactionPoint()
{
	Faction = CreateDefaultSubobject<UFactionComponent>("Faction");	
}
