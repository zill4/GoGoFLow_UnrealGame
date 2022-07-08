// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "OnlineSessionWrapper.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MULTIPLAYER_1_API FOnlineSessionWrapper 
{
	GENERATED_USTRUCT_BODY()
	

	UPROPERTY(BlueprintReadOnly)
	FString ConnectionString;

	UPROPERTY(BlueprintReadOnly)
	int PingInMs;

	UPROPERTY(BlueprintReadOnly)
	FString OwnerUsername;

	UPROPERTY(BlueprintReadOnly)
	FString SessionId;

	FOnlineSessionSearchResult OnlineResult;
};
