#include "InfoWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "LNR/Component/AttributesComponent.h"
#include "LNR/Component/InfoComponent.h"

void UInfoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(Attributes) ValueBar->SetPercent(Attributes->GetHealthPercent());
	else ValueBar->SetPercent(Info->Value);
}

void UInfoWidget::Refresh() const
{
	NameText->SetText(FText::FromString(Info->Name));
	IconImage->SetBrushFromTexture(Info->Icon);
	IconImage->ColorAndOpacity = Info->Color;
	ValueBar->FillColorAndOpacity = Info->Color;
	if(Attributes) ValueBar->SetPercent(Attributes->GetHealthPercent());
	else ValueBar->SetPercent(Info->Value);
}
