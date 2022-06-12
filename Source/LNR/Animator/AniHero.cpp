#include "AniHero.h"
#include "LNR/Body/Hero.h"
#include "Kismet/KismetMathLibrary.h"

void UAniHero::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (Body) Hero = Cast<AHero>(Body);
	const FTransform t = GetOwningComponent()->GetSocketTransform("Camera", RTS_ParentBoneSpace);
	CamSocketLocation = t.GetLocation();
	CamSocketRotation = t.GetRotation().Rotator();
}

void UAniHero::InterpolateSights(const FTransform newSight)
{
	if (LastSight.GetLocation() != newSight.GetLocation())
	{
		LastSight = UKismetMathLibrary::TEase(LastSight, newSight, CycleSightSpeed, EEasingFunc::EaseOut, 2);
		SetIk(LastSight.GetLocation(), LastSight.GetRotation().Rotator(), LastSight.GetScale3D().X);
		const FTimerDelegate del = FTimerDelegate::CreateUObject(this, &UAniHero::InterpolateSights, newSight);
		GetWorld()->GetTimerManager().ClearTimer(InterpolateSightHandle);
		GetWorld()->GetTimerManager().SetTimer(InterpolateSightHandle, del, 0.01, false);
	}
	else GetWorld()->GetTimerManager().ClearTimer(InterpolateSightHandle);
}

void UAniHero::NewSightTransform(const bool interpolate, const FTransform newRelativeToHand)
{
	if (interpolate)
	{
		InterpolateSights(newRelativeToHand);
	}
	else
	{
		LastSight = newRelativeToHand;
		SetIk(LastSight.GetLocation(), LastSight.GetRotation().Rotator(), LastSight.GetScale3D().X);
	}
}

void UAniHero::SetIk(const FVector relativeHandLocation, const FRotator relativeHandRotation, const float distance)
{
	RelativeToHandLocation = relativeHandLocation;
	RelativeToHandRotation = relativeHandRotation;
	SightLocation = FVector(CamSocketLocation.X, CamSocketLocation.Y + distance, CamSocketLocation.Z);
}
