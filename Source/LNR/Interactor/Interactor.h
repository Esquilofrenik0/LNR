#pragma once
#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "LNR/Interface/Interact.h"
#include "Interactor.generated.h"

UCLASS()
class LNR_API AInteractor : public AStaticMeshActor, public IInteract
{
	GENERATED_BODY()
public:
	AInteractor();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UInfoComponent* Info;
	virtual void BeginPlay() override;
	virtual void OnInteract_Implementation(AHero* nHero) override;
	virtual void OnShowInfo_Implementation(AHero* nHero, bool val) override;
};
