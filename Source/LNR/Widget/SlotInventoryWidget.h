#pragma once
#include "SlotWidget.h"
#include "SlotInventoryWidget.generated.h"

UCLASS(Abstract)
class LNR_API USlotInventoryWidget : public USlotWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	class AHero* Hero;
	UPROPERTY(BlueprintReadWrite)
	int SlotNumber;
	void Init(AHero* nHero);
	virtual void Click() override;
};
