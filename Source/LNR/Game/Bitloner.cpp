#include "Bitloner.h"

void UBitloner::Init()
{
	Super::Init();
	// GetTimerManager().ClearTimer(DelayInitHandle);
	// GetTimerManager().SetTimer(DelayInitHandle, this, &UBitloner::DelayInit, 2);
}

void UBitloner::DelayInit()
{
	// GetTimerManager().ClearTimer(DelayInitHandle);
}
