#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InfoCanvas.generated.h"

UCLASS()
class LNR_API UInfoCanvas : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Icon;
	UPROPERTY(BlueprintReadWrite)
	FString Text;
};
