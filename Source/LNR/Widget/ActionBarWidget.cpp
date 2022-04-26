#include "ActionBarWidget.h"
#include "SlotWidget.h"
#include "Components/Image.h"
#include "LNR/Component/ActionComponent.h"

void UActionBarWidget::Init(UActionComponent* nAction)
{
	Action = nAction;
	Refresh();
}

void UActionBarWidget::Refresh() const
{
	if (Action->ActionBar[0] != nullptr) Action1Slot->Setup(Action->ActionBar[0].GetDefaultObject()->Icon);
	else Action1Slot->Setup(nullptr);
	if (Action->ActionBar[1] != nullptr) Action2Slot->Setup(Action->ActionBar[1].GetDefaultObject()->Icon);
	else Action2Slot->Setup(nullptr);
	if (Action->ActionBar[2] != nullptr) Action3Slot->Setup(Action->ActionBar[2].GetDefaultObject()->Icon);
	else Action3Slot->Setup(nullptr);
	if (Action->ActionBar[3] != nullptr) Action4Slot->Setup(Action->ActionBar[3].GetDefaultObject()->Icon);
	else Action4Slot->Setup(nullptr);
}
