#include "ContainerWidget.h"
#include "SlotContainerWidget.h"
#include "Components/WrapBox.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/InventoryComponent.h"

void UContainerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	Refresh();
}

void UContainerWidget::Init(AHero* nHero)
{
	Hero = nHero;
	Slots.Empty();
	TArray<UWidget*> s = SlotBox->GetAllChildren();
	for (int i = 0; i < s.Num(); i++)
	{
		USlotContainerWidget* slot = Cast<USlotContainerWidget>(s[i]);
		slot->SlotNumber = i;
		slot->Init(Hero);
		Slots.Add(slot);
	}
}

void UContainerWidget::Refresh() const
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		if (i < Hero->Container->Slots.Num())
		{
			Slots[i]->SetIsEnabled(true);
			if (Hero->Container->Slots[i].Item != nullptr) Slots[i]->Setup(Hero->Container->Slots[i].Item->Icon);
			else Slots[i]->Setup(nullptr);
		}
		else
		{
			Slots[i]->Setup(nullptr);
			Slots[i]->SetIsEnabled(false);
		}
	}
}
