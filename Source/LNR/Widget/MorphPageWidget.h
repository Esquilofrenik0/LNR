#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LNR/Data/AvatarData.h"
#include "MorphPageWidget.generated.h"

UCLASS(Abstract)
class LNR_API UMorphPageWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<class UMorphSliderWidget> MorphSliderTemplate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FMorphPageData MorphPageData;
	UPROPERTY(BlueprintReadWrite)
	class AAvatar* Avatar;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UVerticalBox* Box;
	UFUNCTION(BlueprintCallable)
	void Init(AAvatar* nAvatar);
};
