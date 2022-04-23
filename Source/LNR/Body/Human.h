#pragma once

#include "CoreMinimal.h"
#include "Body.h"
#include "Human.generated.h"

UCLASS()
class LNR_API AHuman : public ABody
{
	GENERATED_BODY()
public:
	AHuman();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UApparelComponent* Apparel;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UAvatarComponent* Avatar;
	virtual void BeginPlay() override;
};
