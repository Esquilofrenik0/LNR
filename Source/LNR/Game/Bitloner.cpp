#include "Bitloner.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/OnlineIdentityInterface.h"

void UBitloner::Init()
{
	Super::Init();
	GetTimerManager().ClearTimer(DelayInit);
	GetTimerManager().SetTimer(DelayInit, this, &UBitloner::Login, 1);
}

void UBitloner::Login()
{
	GetTimerManager().ClearTimer(DelayInit);
	const IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
	const IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	this->LoginDelegateHandle = Identity->AddOnLoginCompleteDelegate_Handle(
		0, FOnLoginComplete::FDelegate::CreateUObject(this, &UBitloner::HandleLoginComplete));
	if (!Identity->AutoLogin(0))
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Eos login didn't start!");
	}
}

void UBitloner::HandleLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
                                    const FString& Error)
{
	const IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
	const IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	if (bWasSuccessful)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Eos Login Success!");
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, GetLoggedInUsername(this));
	}
	else GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Red, "Eos Login Failed!");
	Identity->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, this->LoginDelegateHandle);
	this->LoginDelegateHandle.Reset();
}

void UBitloner::Logout()
{
	const IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
	const IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	this->LogoutDelegateHandle = Identity->AddOnLogoutCompleteDelegate_Handle(
		0, FOnLogoutComplete::FDelegate::CreateUObject(this, &UBitloner::HandleLogoutComplete));
	if (!Identity->Logout(0))
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Eos logout didn't start!");
	}
}

void UBitloner::HandleLogoutComplete(int32 LocalUserNum, bool bWasSuccessful)
{
	const IOnlineSubsystem* Subsystem = Online::GetSubsystem(this->GetWorld());
	const IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	if (bWasSuccessful)
	{
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Green, "Eos Logout Success!");
	}
	else GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2.00f, FColor::Red, "Eos Logout Failed!");
	Identity->ClearOnLogoutCompleteDelegate_Handle(LocalUserNum, this->LogoutDelegateHandle);
	this->LogoutDelegateHandle.Reset();
}

bool UBitloner::IsSignedIn(const UObject* WorldContextObject)
{
	const IOnlineSubsystem* Subsystem = Online::GetSubsystem(WorldContextObject->GetWorld());
	if (Subsystem == nullptr) return false;
	const IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	return Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn;
}

FString UBitloner::GetLoggedInUsername(const UObject* WorldContextObject)
{
	const IOnlineSubsystem* Subsystem = Online::GetSubsystem(WorldContextObject->GetWorld());
	if (Subsystem == nullptr) return TEXT("");
	const IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	if (Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
	{
		TSharedPtr<const FUniqueNetId> Id = Identity->GetUniquePlayerId(0);
		if (Id.IsValid())
		{
			TSharedPtr<FUserOnlineAccount> Account = Identity->GetUserAccount(*Id);
			if (Account.IsValid())
			{
				if (Account->GetDisplayName().IsEmpty())
				{
					return TEXT("(No Username Set, but you are Logged In)");
				}
				else
				{
					return Account->GetDisplayName();
				}
			}
		}
	}

	return TEXT("Not Logged In");
}

FString UBitloner::GetLoggedInProductUserId(const UObject* WorldContextObject)
{
	const IOnlineSubsystem* Subsystem = Online::GetSubsystem(WorldContextObject->GetWorld());
	if (Subsystem == nullptr) return TEXT("");
	const IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	if (Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
	{
		TSharedPtr<const FUniqueNetId> Id = Identity->GetUniquePlayerId(0);
		if (Id.IsValid())
		{
			TSharedPtr<FUserOnlineAccount> Account = Identity->GetUserAccount(*Id);
			if (Account.IsValid())
			{
				FString OutAttr;
				if (Account->GetUserAttribute(TEXT("productUserId"), OutAttr))
				{
					return OutAttr;
				}
			}
		}
	}

	return TEXT("");
}

FString UBitloner::GetLoggedInEpicAccountId(const UObject* WorldContextObject)
{
	const IOnlineSubsystem* Subsystem = Online::GetSubsystem(WorldContextObject->GetWorld());
	if (Subsystem == nullptr) return TEXT("");
	const IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	if (Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
	{
		TSharedPtr<const FUniqueNetId> Id = Identity->GetUniquePlayerId(0);
		if (Id.IsValid())
		{
			TSharedPtr<FUserOnlineAccount> Account = Identity->GetUserAccount(*Id);
			if (Account.IsValid())
			{
				FString OutTypes;
				if (Account->GetUserAttribute(TEXT("externalAccountTypes"), OutTypes))
				{
					TArray<FString> TypesArr;
					OutTypes.ParseIntoArray(TypesArr, TEXT(","));
					if (TypesArr.Contains("epic"))
					{
						FString OutAttr;
						if (Account->GetUserAttribute(TEXT("externalAccount.epic.id"), OutAttr))
						{
							return OutAttr;
						}
					}
				}
			}
		}
	}

	return TEXT("");
}

FString UBitloner::GetLoggedInAuthAttribute(const UObject* WorldContextObject, const FString& InAuthAttrName)
{
	const IOnlineSubsystem* Subsystem = Online::GetSubsystem(WorldContextObject->GetWorld());
	if (Subsystem == nullptr) return TEXT("");
	const IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	if (Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
	{
		TSharedPtr<const FUniqueNetId> Id = Identity->GetUniquePlayerId(0);
		if (Id.IsValid())
		{
			TSharedPtr<FUserOnlineAccount> Account = Identity->GetUserAccount(*Id);
			if (Account.IsValid())
			{
				FString OutAttr;
				if (Account->GetAuthAttribute(InAuthAttrName, OutAttr))
				{
					return OutAttr;
				}
			}
		}
	}

	return TEXT("");
}

FUniqueNetIdRepl UBitloner::GetLoggedInUserId(const UObject* WorldContextObject)
{
	const IOnlineSubsystem* Subsystem = Online::GetSubsystem(WorldContextObject->GetWorld());
	if (Subsystem == nullptr) return FUniqueNetIdRepl();
	const IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	if (Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
	{
		TSharedPtr<const FUniqueNetId> Id = Identity->GetUniquePlayerId(0);
		if (Id.IsValid()) return FUniqueNetIdRepl(Id);
	}
	return FUniqueNetIdRepl();
}

bool UBitloner::CanLinkToEpicGamesAccount(const UObject* WorldContextObject)
{
	const IOnlineSubsystem* Subsystem = Online::GetSubsystem(WorldContextObject->GetWorld());
	if (Subsystem == nullptr) return false;
	const IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	if (Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
	{
		TSharedPtr<const FUniqueNetId> Id = Identity->GetUniquePlayerId(0);
		if (Id.IsValid())
		{
			TSharedPtr<FUserOnlineAccount> Account = Identity->GetUserAccount(*Id);
			if (Account.IsValid())
			{
				FString OutVal;
				if (Account->GetAuthAttribute(TEXT("crossPlatform.canLink"), OutVal))
				{
					return OutVal == TEXT("true");
				}
			}
		}
	}
	return false;
}
