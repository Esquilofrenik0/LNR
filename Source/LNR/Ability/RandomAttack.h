#pragma once
#include "CoreMinimal.h"
#include "Attack.h"
#include "RandomAttack.generated.h"

UCLASS()
class LNR_API URandomAttack : public UAttack
{
	GENERATED_BODY()
public:
	virtual void PreAttack(ABody* body) override;
};
