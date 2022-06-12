#pragma once
#include "CoreMinimal.h"
#include "MarkerComponent.generated.h"

UCLASS()
class LNR_API UMarkerComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UMarkerComponent();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Icon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor Color;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Discovered;
	UPROPERTY(BlueprintReadWrite)
	class UControlPoint* ControlPoint;
};
