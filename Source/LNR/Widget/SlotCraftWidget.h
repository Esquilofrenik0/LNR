#pragma once
#include "SlotWidget.h"
#include "SlotCraftWidget.generated.h"

UCLASS()
class LNR_API USlotCraftWidget : public USlotWidget
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
