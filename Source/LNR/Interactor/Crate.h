#pragma once
#include "Container.h"
#include "Crate.generated.h"

UCLASS(Abstract)
class LNR_API ACrate : public AContainer
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UDataTable* Dropables;
	UPROPERTY(BlueprintReadWrite)
	int MaxAliveTime = 60;
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle DestroyHandle;
	
	virtual void OnInteract_Implementation(class AHero* nHero) override;
	virtual void Close() override;
	void DestroyThis();

	UFUNCTION(BlueprintCallable)
	void GenerateLoot();
	UFUNCTION(Server, Reliable)
	void ServerGenerateLoot();
	void ServerGenerateLoot_Implementation() { GenerateLoot(); }

};
