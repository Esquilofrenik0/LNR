#pragma once
#include "Engine/DataTable.h"
#include "DialogOption.generated.h"

USTRUCT(BlueprintType)
struct LNR_API FDialogSpeech : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> Speech;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Target;

	FDialogSpeech()
	{
		Speech.Empty();
		Target = "";
	}
};

USTRUCT(BlueprintType)
struct LNR_API FDialogChoice : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Choice;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Target;

	FDialogChoice()
	{
		Choice = "";
		Target = "";
	}
};


USTRUCT(BlueprintType)
struct LNR_API FDialogOption : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FDialogSpeech Speech;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FDialogChoice> Choices;

	FDialogOption()
	{
		Speech = FDialogSpeech();
		Choices.Empty();
	}
};