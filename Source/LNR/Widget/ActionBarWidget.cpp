#include "ActionBarWidget.h"
#include "SlotWidget.h"
#include "Components/Image.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/ActionComponent.h"
#include "LNR/Component/EquipmentComponent.h"

void UActionBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	Refresh();
}

void UActionBarWidget::Init(AHero* nHero)
{
	Hero = nHero;
}

void UActionBarWidget::Refresh() const
{
	if (Hero->BlockPressed)
	{
		if (Hero->Equipment->Consumable[0].Consumable != nullptr && Hero->Equipment->Consumable[0].Amount > 0) Action1Slot->Setup(Hero->Equipment->Consumable[0].Consumable->Icon);
		else Action1Slot->Setup(nullptr);
		if (Hero->Equipment->Consumable[1].Consumable != nullptr && Hero->Equipment->Consumable[1].Amount > 0) Action2Slot->Setup(Hero->Equipment->Consumable[1].Consumable->Icon);
		else Action2Slot->Setup(nullptr);
		if (Hero->Equipment->Consumable[2].Consumable != nullptr && Hero->Equipment->Consumable[2].Amount > 0) Action3Slot->Setup(Hero->Equipment->Consumable[2].Consumable->Icon);
		else Action3Slot->Setup(nullptr);
		if (Hero->Equipment->Consumable[3].Consumable != nullptr && Hero->Equipment->Consumable[3].Amount > 0) Action4Slot->Setup(Hero->Equipment->Consumable[3].Consumable->Icon);
		else Action4Slot->Setup(nullptr);
	}
	else
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
}
