#include "LNR.h"
#include "Modules/ModuleManager.h"
#include "Kismet/KismetSystemLibrary.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, LNR, "LNR" );

void Print(FString print)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, print);
}

void Print(int print)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, FString::FromInt(print));
}

void Print(float print)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, FString::SanitizeFloat(print));
}