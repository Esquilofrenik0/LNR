#pragma once
#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "LNR/Data/AvatarData.h"
#include "LNR/Data/FactionData.h"
#include "LNR/Data/HarvestingData.h"
#include "LNR/Interactor/Tombstone.h"
#include "Bitloner.generated.h"

UCLASS()
class LNR_API UBitloner final : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAvatarGlobals AvatarGlobals;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFactionGlobals FactionGlobals;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHarvestingData HarvestingData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATombstone> Tombstone;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTexture2D*> InteractionType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* DefaultMask;
	
	FTimerHandle DelayInit;
	UFUNCTION(BlueprintCallable)
	virtual void Init() override;

	FDelegateHandle LoginDelegateHandle;
	UFUNCTION(BlueprintCallable)
	void Login();
	void HandleLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	FDelegateHandle LogoutDelegateHandle;
	UFUNCTION(BlueprintCallable)
	void Logout();
	void HandleLogoutComplete(int32 LocalUserNum, bool bWasSuccessful);
	
	static bool IsSignedIn(const UObject* WorldContextObject);
	static FString GetLoggedInUsername(const UObject* WorldContextObject);
	static FString GetLoggedInProductUserId(const UObject* WorldContextObject);
	static FString GetLoggedInEpicAccountId(const UObject* WorldContextObject);
	static FString GetLoggedInAuthAttribute(const UObject* WorldContextObject, const FString& InAuthAttrName);
	static FUniqueNetIdRepl GetLoggedInUserId(const UObject* WorldContextObject);
	static bool CanLinkToEpicGamesAccount(const UObject* WorldContextObject);
};
