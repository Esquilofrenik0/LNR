#pragma once
#include "AniPawn.h"
#include "AniBody.generated.h"

UCLASS(transient, Blueprintable, hideCategories=AnimInstance, BlueprintType)
class LNR_API UAniBody : public UAniPawn
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ABody* Body;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(const float deltaTimeX) override;
};
