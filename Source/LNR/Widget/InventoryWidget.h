#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

UCLASS()
class LNR_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UBagWidget* BagWidget;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UEquipmentWidget* EquipmentWidget;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UCraftWidget* CraftWidget;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UContainerWidget* ContainerWidget;
	void Init(class AHero* nHero) const;
};
