#include "FactionPoint.h"
#include "Kismet/GameplayStatics.h"
#include "LNR/Body/Body.h"
#include "LNR/Game/Bitloner.h"

void UFactionPoint::BeginPlay()
{
	Super::BeginPlay();
	Bitloner = Cast<UBitloner>(UGameplayStatics::GetGameInstance(this));
}