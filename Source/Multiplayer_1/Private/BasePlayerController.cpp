// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

ABasePlayerController::ABasePlayerController()
{
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}


void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Set initial character
	MainCharacter = Cast<AMultiplayer_1Character>(GetPawn());
}

void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

}

void ABasePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	OnPawnChanged.Broadcast(InPawn);
}