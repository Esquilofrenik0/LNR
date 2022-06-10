#pragma once
#include "CoreMinimal.h"
#include "Macro.generated.h"

UCLASS()
class LNR_API UMacro : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static FString GetRealName(const UObject* obj);
	static FString GetRealName(FString n);
};
