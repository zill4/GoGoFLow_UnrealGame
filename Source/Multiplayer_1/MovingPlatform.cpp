// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {

	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay() {

	Super::BeginPlay();
	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime) {

	//Use the Super method when overriding classes

	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		// safe normal doesn't modify in lplace
		float  JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JounrneyTravelled = (Location - GlobalStartLocation).Size();
	
		if (JounrneyTravelled >= JourneyLength)
		{
			FVector temp = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = temp;
		}


		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += Speed * Direction * DeltaTime;
		SetActorLocation(Location);
	}
}