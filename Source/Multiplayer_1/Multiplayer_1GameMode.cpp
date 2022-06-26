// Copyright Epic Games, Inc. All Rights Reserved.

#include "Multiplayer_1GameMode.h"
#include "Multiplayer_1Character.h"
#include "UObject/ConstructorHelpers.h"

AMultiplayer_1GameMode::AMultiplayer_1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
