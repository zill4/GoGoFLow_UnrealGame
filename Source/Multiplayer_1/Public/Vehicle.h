// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Vehicle.generated.h"

UCLASS()
class MULTIPLAYER_1_API AVehicle : public APawn
{
	GENERATED_BODY()
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	// Sets default values for this pawn's properties
	AVehicle();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Vehicle | Collision")
	class UBoxComponent* OverlapComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void OnOverlapBegin( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	// The maximum force applied to the vehicle at full throttle (N).
	// 10_000 / 1_000 = gives force of 10 Newtons
	UPROPERTY(EditAnywhere)
	float MaxForce = 10000;
	
	// The number of degrees rotated per second at full SteeringAngle (degrees/sec).
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 90;

	UPROPERTY(EditAnywhere)
	float DragCoefficient = 16;

	UPROPERTY(EditAnywhere)
	float RollingResistanceCoefficient = .015;

	//Minimum turning of vehicle turning circle at full throttle (m)
	UPROPERTY(EditAnywhere)
	float MinTurningRadius = 5;

	FVector Velocity;

	// The mass of the car in kg.
	UPROPERTY(EditAnywhere)
	float Mass = 1000;

	float Throttle;

	float SteeringAngle;

private:

	void MoveForward(float XAxis);

	void MoveRight(float YAxis);

	void UpdateLocationFromThrottle(float DeltaTime);

	void UpdateRotationFromSteer(float DeltaTime);

	FVector GetAirResistance();
	FVector GetRollingResistance();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
