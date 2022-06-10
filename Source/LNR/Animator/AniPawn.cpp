#include "AniPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PawnMovementComponent.h"
#include "AnimGraphRuntime/Public/KismetAnimationLibrary.h"

void UAniPawn::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Pawn = TryGetPawnOwner();
	if (Pawn) Movement = Pawn->GetMovementComponent();
}

void UAniPawn::NativeUpdateAnimation(const float deltaTimeX)
{
	Super::NativeUpdateAnimation(deltaTimeX);
	if (Pawn)
	{
		const FVector velocity = Pawn->GetVelocity();
		Speed = velocity.Size();
		Direction = UKismetAnimationLibrary::CalculateDirection(velocity, Pawn->GetActorRotation());
		Depth = velocity.Z;
		if (Movement)
		{
			IsInAir = Movement->IsFalling();
			IsCrouching = Movement->IsCrouching();
		}
	}
}
