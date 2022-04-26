#include "ActionBarWidget.h"
#include "SlotWidget.h"
#include "Components/Image.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/ActionComponent.h"

void UActionBarWidget::Init(AHero* nHero)
{
	Hero = nHero;
	Refresh();
}

void UActionBarWidget::Refresh() const
{
	if (Hero->Action->ActionBar[0] != nullptr) Action1Slot->Setup(Hero->Action->ActionBar[0].GetDefaultObject()->Icon);
	else Action1Slot->Setup(nullptr);
	if (Hero->Action->ActionBar[1] != nullptr) Action2Slot->Setup(Hero->Action->ActionBar[1].GetDefaultObject()->Icon);
	else Action2Slot->Setup(nullptr);
	if (Hero->Action->ActionBar[2] != nullptr) Action3Slot->Setup(Hero->Action->ActionBar[2].GetDefaultObject()->Icon);
	else Action3Slot->Setup(nullptr);
	if (Hero->Action->ActionBar[3] != nullptr) Action4Slot->Setup(Hero->Action->ActionBar[3].GetDefaultObject()->Icon);
	else Action4Slot->Setup(nullptr);
}
