// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYER_1_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

	UPROPERTY(EditAnywhere)
	float Speed = 15;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

protected:
	// Is protected to match the parent class
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override; 

private:
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;

};
