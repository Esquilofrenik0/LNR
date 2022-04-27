#pragma once
#include "CoreMinimal.h"
#include "Humanoid.h"
#include "Human.generated.h"

UCLASS()
class LNR_API AHuman : public AHumanoid
{
	GENERATED_BODY()
public:
	AHuman();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UApparelComponent* Apparel;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAvatarComponent* Avatar;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
};
