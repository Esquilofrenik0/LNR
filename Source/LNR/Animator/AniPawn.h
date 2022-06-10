#pragma once
#include "Animation/AnimInstance.h"
#include "AniPawn.generated.h"

UCLASS(transient, Blueprintable, hideCategories=AnimInstance, BlueprintType)
class LNR_API UAniPawn : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APawn* Pawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPawnMovementComponent* Movement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Depth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsCrouching;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(const float deltaTimeX) override;
};
