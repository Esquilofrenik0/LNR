#include "PlayerAvatar.h"
#include "HudAvatar.h"

void APlayerAvatar::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (AHUD* nHud = GetHUD()) Hud = Cast<AHudAvatar>(nHud);
}
