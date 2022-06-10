#include "AniBody.h"
#include "LNR/Body/Body.h"

void UAniBody::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if(Pawn) Body = Cast<ABody>(Pawn);
}

void UAniBody::NativeUpdateAnimation(const float deltaTimeX)
{
	Super::NativeUpdateAnimation(deltaTimeX);
	if(Body)
	{
		
	}
}
