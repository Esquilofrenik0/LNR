#include "WorldMapWidget.h"
#include "SlotWidget.h"
#include "MarkerWidget.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/NavigationComponent.h"
#include "LNR/Game/Playor.h"
#include "LNR/Component/MarkerComponent.h"
#include "LNR/PointOfInterest/ControlPoint.h"

void UWorldMapWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	Refresh();
}

void UWorldMapWidget::Init(APlayor* playor)
{
	Player = playor;
}

void UWorldMapWidget::Refresh()
{
	for (int i = 0; i < Player->Navigation->Marker.Num(); i++)
	{
		// if (Player->Navigation->Marker[i])
		// {
			DrawMarker(Player->Navigation->Marker[i]);
		// }
		// else HideMarker(Player->Navigation->Marker[i]);
	}
}

void UWorldMapWidget::DrawMarker(UMarkerComponent* nMarker)
{
	int index = -1;
	for (int i = 0; i < Marker.Num(); i++)
	{
		if (Marker[i]->Marker == nMarker)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		UWidget* widget = CreateWidget(this, MarkerTemplate);
		Panel->AddChild(widget);
		UMarkerWidget* mark = Cast<UMarkerWidget>(widget);
		mark->Init(nMarker);
		index = Marker.Add(mark);
	}
}

void UWorldMapWidget::HideMarker(const UMarkerComponent* nMarker)
{
	int index = -1;
	for (int i = 0; i < Marker.Num(); i++)
	{
		if (Marker[i]->Marker == nMarker)
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		Marker[index]->Destruct();
		Marker.RemoveAt(index);
	}
}
