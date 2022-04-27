#pragma once
#include "SlotWidget.h"
#include "SlotContainerWidget.generated.h"

UCLASS()
class LNR_API USlotContainerWidget : public USlotWidget
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
