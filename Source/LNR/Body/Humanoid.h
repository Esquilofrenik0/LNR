#pragma once

#include "CoreMinimal.h"
#include "Body.h"
#include "Humanoid.generated.h"

UCLASS()
class LNR_API AHumanoid : public ABody
{
	GENERATED_BODY()
public:
	AHumanoid();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UEquipmentComponent* Equipment;
	virtual void RefreshAttributes() override;
};
