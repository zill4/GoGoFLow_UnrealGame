// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Multiplayer_1GameMode.generated.h"

UCLASS(minimalapi)
class AMultiplayer_1GameMode : public AGameModeBase
{
	GENERATED_BODY()



protected:
	AMultiplayer_1GameMode();

public:
	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void StartPlay() override;

	void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

};



