#include "HudMenuWidget.h"
#include "HudAvatarWidget.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

void UHudMenuWidget::Init(AHudMenu* nHud, APlayerMenu* nPlayer)
{
	Hud = nHud;
	Player = nPlayer;
	if (HudAvatarTemplate)
	{
		HudAvatarWidget = CreateWidget<UHudAvatarWidget>(GetWorld(), HudAvatarTemplate);
		if (HudAvatarWidget)
		{
			HudAvatarWidget->Init(Hud);
			UOverlaySlot* slot = AvatarOverlay->AddChildToOverlay(HudAvatarWidget);
			slot->SetHorizontalAlignment(HAlign_Fill);
			slot->SetVerticalAlignment(VAlign_Fill);
		}
	}
}
