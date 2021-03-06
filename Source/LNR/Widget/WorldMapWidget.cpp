#include "WorldMapWidget.h"
#include "SlotWidget.h"
#include "MarkerWidget.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/NavigationComponent.h"
#include "LNR/Component/MarkerComponent.h"

void UWorldMapWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (Hero) Refresh();
}

void UWorldMapWidget::Init(AHero* nHero)
{
	Hero = nHero;
}

void UWorldMapWidget::Refresh()
{
	DrawPlayerMarker();
	for (int i = 0; i < Hero->Navigation->Marker.Num(); i++)
	{
		if (Hero->Navigation->Discovered.Contains(Hero->Navigation->Marker[i]->Id))
		{
			DrawMarker(Hero->Navigation->Marker[i]);
		}
		else HideMarker(Hero->Navigation->Marker[i]);
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
		UOverlaySlot* slot = Panel->AddChildToOverlay(widget);
		slot->SetHorizontalAlignment(HAlign_Center);
		slot->SetVerticalAlignment(VAlign_Center);
		UMarkerWidget* mark = Cast<UMarkerWidget>(widget);
		mark->Init(nMarker);
		index = Marker.Add(mark);
	}
	const FVector mLoc = Marker[index]->Marker->GetOwner()->GetActorLocation();
	Marker[index]->Distance->SetText(FText::FromName(Marker[index]->Marker->Id));
	const float x = UKismetMathLibrary::MapRangeClamped(mLoc.X, -400000, 400000, -500, 500);
	const float y = UKismetMathLibrary::MapRangeClamped(mLoc.Y, -400000, 400000, -500, 500);
	Marker[index]->SetRenderTranslation(FVector2D(x, y));;
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

void UWorldMapWidget::DrawPlayerMarker() const
{
	const FVector heroLoc = Hero->GetActorLocation();
	const float x = UKismetMathLibrary::MapRangeClamped(heroLoc.X, -400000, 400000, -500, 500);
	const float y = UKismetMathLibrary::MapRangeClamped(heroLoc.Y, -400000, 400000, -500, 500);
	PlayerMarker->SetRenderTranslation(FVector2D(x, y));;
}
