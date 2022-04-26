#include "BagWidget.h"
#include "SlotWidget.h"
#include "Components/WrapBox.h"
#include "LNR/Component/InventoryComponent.h"

void UBagWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Slots.Empty();
	TArray<UWidget*> s = SlotBox->GetAllChildren();
	for (int i = 0; i < s.Num(); i++) Slots.Add(Cast<USlotWidget>(s[i]));
}

void UBagWidget::Refresh(UInventoryComponent* inventory) const
{
	for (int i = 0; i < Slots.Num(); i++)
	{
		if (i < inventory->Slots.Num())
		{
			Slots[i]->SetIsEnabled(true);
			if (inventory->Slots[i].Item != nullptr) Slots[i]->Setup(inventory->Slots[i].Item->Icon);
			else Slots[i]->Setup(nullptr);
		}
		else
		{
			Slots[i]->Setup(nullptr);
			Slots[i]->SetIsEnabled(false);
		}
	}
}
