// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameInstance.h"
#include "OnlineSessionWrapper.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_1_API UOnlineGameInstance : public UBaseGameInstance
{
	GENERATED_BODY()
	
public:
	UOnlineGameInstance();

	virtual void Init() override;

	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable)
	void CreateSession();

	UFUNCTION(BlueprintCallable)
	void DestroySession(bool bShutdown);

	UFUNCTION(BlueprintCallable)
	void FindSessions();

	UFUNCTION(BlueprintCallable)
	void JoinOnlineSession(FOnlineSessionWrapper Session);

	UFUNCTION(BlueprintCallable)
	void Login(FString Username);

	UFUNCTION(BlueprintCallable)
	void Logout();

	//UPROPERTY(BlueprintAssignable)
	//FOnFindSessionsCompleteDelegate  SessionFoundCompleteDelegate;

	//UPROPERTY(BlueprintAssignable)
	//FOnLoginCompleteDelegate LoginCompleteDelegate;

	//UPROPERTY(BlueprintAssignable)
	//FOnLogoutCompleteDelegate LogoutCompleteDelegate;

	UPROPERTY(BlueprintReadOnly)
	bool bIsLoggedIn;

private:

	FName LocalServerSessionName;

	FName LocalClientSessionName;

	bool bShouldShutdown;

	class IOnlineSubsystem* OnlineSubsystem;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	void OnLoginComplete(int ControllerIndex, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& ErrorString);

	void OnLogoutComplete(int ControllerIndex, bool bWasSuccessful);

	void OnSessionCreated(FName SessionName, bool bWasSuccessful);

	void OnSessionDestroyed(FName SessionName, bool bWasSuccessful);

	void OnFindSessionsComplete(bool bWasSuccessful);

	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

};
