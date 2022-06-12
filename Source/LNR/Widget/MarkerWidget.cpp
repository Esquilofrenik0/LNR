#include "MarkerWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "LNR/Component/MarkerComponent.h"
#include "LNR/PointOfInterest/ControlPoint.h"

void UMarkerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	Refresh();
}

void UMarkerWidget::Init(UMarkerComponent* nMarker)
{
	Marker = nMarker;
	Refresh();
}

void UMarkerWidget::Refresh() const
{
	Image->SetBrushFromTexture(Marker->Icon);
	Image->SetColorAndOpacity(Marker->Color);
	// Distance->SetColorAndOpacity(FSlateColor(Marker->Color));
	if (Marker->ControlPoint)
	{
		ProgressBar->SetVisibility(ESlateVisibility::HitTestInvisible);
		ProgressBar->SetPercent(Marker->ControlPoint->Influence);
		ProgressBar->SetFillColorAndOpacity(Marker->Color);
	}
	else ProgressBar->SetVisibility(ESlateVisibility::Hidden);
}
