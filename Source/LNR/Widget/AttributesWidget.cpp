#include "AttributesWidget.h"
#include "Components/ProgressBar.h"
#include "LNR/Component/AttributesComponent.h"

void UAttributesWidget::Init(UAttributesComponent* nAttributes)
{
	Attributes = nAttributes;
}

void UAttributesWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	HealthBar->SetPercent(Attributes->GetHealthPercent());
	StaminaBar->SetPercent(Attributes->GetStaminaPercent());
	EnergyBar->SetPercent(Attributes->GetEnergyPercent());
	WantedBar->SetPercent(Attributes->GetWantedPercent());
}
