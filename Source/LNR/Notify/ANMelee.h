#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "LNR/Body/Body.h"
#include "ANMelee.generated.h"

UCLASS()
class LNR_API UANMelee : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	ABody* Body;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> MeleeSockets;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MeleeSocketRadius = 50;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
};
