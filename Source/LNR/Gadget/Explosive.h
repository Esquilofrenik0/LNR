#pragma once
#include "CoreMinimal.h"
#include "XFireInterface.h"
#include "GadgetBase.h"
#include "Explosive.generated.h"

UCLASS(Abstract, Blueprintable)
class LNR_API AExplosive : public AGadgetBase, public IXFireInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage = 10;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ExplosionSize = 100;
	
	UPROPERTY(BlueprintReadWrite)
	class AXFireManager* FireManager;

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void Explode(FVector location);
	UFUNCTION(Server, Reliable)
	void ServerExplode(FVector location);
	void ServerExplode_Implementation(FVector location) { OnExplode(location); };
	UFUNCTION(BlueprintImplementableEvent)
	void OnExplode(FVector location);
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;
	virtual void FireDamage_Implementation(UXFireInstance* XFireInstance, FXFireSettings XFireSettings, float MaxDamage,
	                                       float Damage) override;
};