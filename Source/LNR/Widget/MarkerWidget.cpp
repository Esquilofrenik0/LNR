#include "MarkerWidget.h"
#include "Components/Image.h"
#include "LNR/Component/MarkerComponent.h"

void UMarkerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMarkerWidget::Init(UMarkerComponent* nMarker)
{
	Marker = nMarker;
	Image->SetBrushFromTexture(Marker->Icon);
	Image->SetColorAndOpacity(Marker->Color);
}

void UMarkerWidget::Refresh() const
{
}
 