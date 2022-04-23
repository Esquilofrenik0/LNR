#pragma once
#include "CoreMinimal.h"
#include "Consumable.h"
#include "Aid.generated.h"

UCLASS(Abstract)
class LNR_API UAid : public UConsumable
{
	GENERATED_BODY()
public:
	UAid();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float HealthRestore;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StaminaRestore;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FocusRestore;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMesh* StaticMesh;
	
	virtual void Consume_Implementation(ABody* nBody) override;
};
