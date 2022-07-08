// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Multiplayer_1/Multiplayer_1Character.h"
#include "Multiplayer_1/Public/Vehicle.h"
#include "BasePlayerController.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPawnChanged, APawn*, NewPawn);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChanged, APlayerState*, NewPlayerState);

/**
 * 
 */
UCLASS()
class MULTIPLAYER_1_API ABasePlayerController : public APlayerController
{
	
	GENERATED_BODY()
	
public:

	ABasePlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;

	AMultiplayer_1Character* MainCharacter;
	AVehicle* vehicle;

protected:
	

	UPROPERTY(BlueprintAssignable)
	FOnPawnChanged  OnPawnChanged;

	// Listen for incoming player state (for clients this may be nullptr when initially joining a game, 
	// afterwards player state will not change again as PlayerControllers maintain the same player state throughout the level)
	UPROPERTY(BlueprintAssignable)
	FOnPlayerStateChanged OnPlayerStateReceived;


};
