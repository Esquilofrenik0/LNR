#pragma once
#include "GameFramework/Character.h"
#include "LNR/Interface/Interact.h"
#include "Soul.generated.h"

UCLASS()
class LNR_API ASoul : public ACharacter, public IInteract
{
	GENERATED_BODY()
public:
	ASoul();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UNavigationInvokerComponent* NavigationInvoker;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	class UInfoComponent* Info;
	
	virtual void OnInteract_Implementation(AHero* hero) override;
	virtual void OnShowInfo_Implementation(AHero* hero, bool val) override;
};
