#include "AttributesWidget.h"
#include "Components/ProgressBar.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/AttributesComponent.h"

void UAttributesWidget::Init(AHero* nHero)
{
	Hero = nHero;
}

void UAttributesWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	HealthBar->SetPercent(Hero->Attributes->GetHealthPercent());
	StaminaBar->SetPercent(Hero->Attributes->GetStaminaPercent());
	EnergyBar->SetPercent(Hero->Attributes->GetEnergyPercent());
	WantedBar->SetPercent(Hero->Attributes->GetWantedPercent());
}
