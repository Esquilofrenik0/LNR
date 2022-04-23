#pragma once
#include "Engine/DataTable.h"
#include "AvatarData.generated.h"

UENUM()
enum EGender { Male, Female };

USTRUCT(BlueprintType)
struct LNR_API FAvatarData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EGender> Body = Male;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hair = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Beard = 0;
};
