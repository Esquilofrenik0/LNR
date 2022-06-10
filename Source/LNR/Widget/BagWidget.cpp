#include "BagWidget.h"
#include "SlotInventoryWidget.h"
#include "Components/WrapBox.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/InventoryComponent.h"

void UBagWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	Refresh();
}

void UBagWidget::Init(AHero* nHero)
{
	Hero = nHero;
	Slots.Empty();
	TArray<UWidget*> s = SlotBox->GetAllChildren();
	for (int i = 0; i < s.Num(); i++)
	{
		USlotInventoryWidget* slot = Cast<USlotInventoryWidget>(s[i]);
		slot->SlotNumber = i;
		slot->Init(Hero);
		Slots.Add(slot);
	}
}

void UBagWidget::Refresh() const
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		if (i < Hero->Inventory->Slots.Num())
		{
			Slots[i]->SetIsEnabled(true);
			if (Hero->Inventory->Slots[i].Item != nullptr)
			{
				Slots[i]->Setup(Hero->Inventory->Slots[i].Item->Icon, Hero->Inventory->Slots[i].Amount);
			}
			else Slots[i]->Setup(nullptr);
		}
		else
		{
			Slots[i]->Setup(nullptr);
			Slots[i]->SetIsEnabled(false);
		}
	}
}
