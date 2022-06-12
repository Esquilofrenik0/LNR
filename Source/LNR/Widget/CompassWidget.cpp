#include "CompassWidget.h"
#include "SlotWidget.h"
#include "MarkerWidget.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMathLibrary.h"
#include "LNR/Body/Hero.h"
#include "LNR/Component/NavigationComponent.h"
#include "LNR/Game/Playor.h"
#include "LNR/Component/MarkerComponent.h"
#include "LNR/PointOfInterest/ControlPoint.h"

void UCompassWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	Refresh();
}

void UCompassWidget::Init(APlayor* playor)
{
	Player = playor;
	CompassMaterial = Compass->GetDynamicMaterial();
}

void UCompassWidget::Refresh()
{
	CompassMaterial->SetScalarParameterValue("PlayerInput", Player->GetControlRotation().Yaw / 360);
	for (int i = 0; i < Player->Navigation->Marker.Num(); i++)
	{
		if (UKismetMathLibrary::Vector_Distance(Player->Hero->GetActorLocation(),
		                                        Player->Navigation->Marker[i]->
		                                        GetOwner()->GetActorLocation()) < Player->Navigation->DrawDistance)
		{
			DrawMarker(Player->Navigation->Marker[i]);
		}
		else HideMarker(Player->Navigation->Marker[i]);
	}
}

void UCompassWidget::DrawMarker(UMarkerComponent* nMarker)
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
	const FVector heroLoc = Player->Hero->GetActorLocation();
	const FRotator heroRot = Player->GetControlRotation();
	const FVector mLoc = Marker[index]->Marker->GetOwner()->GetActorLocation();
	int loc = ((heroRot.Yaw - UKismetMathLibrary::FindLookAtRotation(mLoc, heroLoc).Yaw) / 360) * 600;
	if (loc < 0) loc = 600 + loc;
	loc = UKismetMathLibrary::MapRangeClamped(loc % 600, 0, 600, 600, -600);
	if (loc < -300 || loc > 300) Marker[index]->SetVisibility(ESlateVisibility::Hidden);
	else
	{
		const float dist = UKismetMathLibrary::Vector_Distance(heroLoc, mLoc) / 100;
		Marker[index]->Distance->SetText(FText::FromString(FString::FromInt(dist)));
		Marker[index]->SetRenderTranslation(FVector2D(loc, 0));;
		Marker[index]->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UCompassWidget::HideMarker(const UMarkerComponent* nMarker)
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
