#include "FactionPoint.h"
#include "LNR/Game/Bitloner.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/Component/MarkerComponent.h"

UFactionPoint::UFactionPoint()
{
	Faction = CreateDefaultSubobject<UFactionComponent>("Faction");
}

void UFactionPoint::BeginPlay()
{
	Super::BeginPlay();
	Faction->Bitloner = Cast<UBitloner>(UGameplayStatics::GetGameInstance(this));
	if (Marker->Icon == nullptr) Marker->Icon = Faction->GetFactionIcon();
	Marker->Color = Faction->GetFactionColor();
}
