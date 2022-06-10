#pragma once
#include "AniBody.h"
#include "AniHero.generated.h"

UCLASS(transient, Blueprintable, hideCategories=AnimInstance, BlueprintType)
class LNR_API UAniHero : public UAniBody
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AHero* Hero;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CycleSightSpeed = 0.5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector CamSocketLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator CamSocketRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RelativeToHandLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator RelativeToHandRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform LastSight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SightLocation = FVector(-15,30,0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle InterpolateSightHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator PitchPerBone;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(const float deltaTimeX) override;
	UFUNCTION(BlueprintCallable)
	void InterpolateSights(const FTransform newSight);
	UFUNCTION(BlueprintCallable)
	void NewSightTransform(const bool interpolate, const FTransform newRelativeToHand);
	UFUNCTION(BlueprintCallable)
	void SetIk(const FVector relativeHandLocation, const FRotator relativeHandRotation, const float distance);
};
