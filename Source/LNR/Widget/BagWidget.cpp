#include "BagWidget.h"
#include "SlotWidget.h"
#include "Components/WrapBox.h"

void UBagWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Slots.Empty();
	TArray<UWidget*> s = SlotBox->GetAllChildren();
	for (int i = 0; i < s.Num(); i++) Slots.Add(Cast<USlotWidget>(s[i]));
}
