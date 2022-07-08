// Copyright Epic Games, Inc. All Rights Reserved.

#include "Multiplayer_1GameMode.h"
#include "Multiplayer_1Character.h"
#include "UObject/ConstructorHelpers.h"
#include "BasePlayerController.h"

AMultiplayer_1GameMode::AMultiplayer_1GameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}

	PlayerControllerClass = ABasePlayerController::StaticClass();
}

void AMultiplayer_1GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AMultiplayer_1GameMode::StartPlay()
{
	Super::StartPlay();
}

void AMultiplayer_1GameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}