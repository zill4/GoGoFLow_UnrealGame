// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"


// Sets default values
AVehicle::AVehicle()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	
	RootComponent = OverlapComponent;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

// Called when the game starts or when spawned
void AVehicle::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);

		OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &AVehicle::OnOverlapBegin);
	}
}

void AVehicle::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Create loading state for loading circleThrobber before net request
	// After request turn throbber off.
	if (GEngine)
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Overlapped from c++"));
	OtherActor->GetInstigatorController()->SetPawn(this);
	OtherActor->GetInstigatorController()->Possess(this);

}


// Called every frame
void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateRotationFromSteer(DeltaTime);

	UpdateLocationFromThrottle(DeltaTime);

}

void AVehicle::UpdateRotationFromSteer(float DeltaTime)
{

	float DeltaLoction = FVector::DotProduct(GetActorForwardVector(), Velocity) * DeltaTime;
	float RotationAngle = SteeringAngle * (DeltaLoction / MinTurningRadius);

	FQuat DeltaRotation(GetActorUpVector(), RotationAngle);

	Velocity = DeltaRotation.RotateVector(Velocity);

	AddActorWorldRotation(DeltaRotation);
}

void AVehicle::UpdateLocationFromThrottle(float DeltaTime)
{
	FVector Force = GetActorForwardVector() * MaxForce * Throttle;

	Force += GetAirResistance();

	Force += GetRollingResistance();

	FVector Acceleration = Force / Mass;

	Velocity = Velocity + (Acceleration * DeltaTime);
	// 100 set centi-meters from meters
	FVector DeltaTranslation = Velocity * DeltaTime * 100;

	FHitResult Hit;

	AddActorWorldOffset(DeltaTranslation, true, &Hit);

	if (Hit.IsValidBlockingHit()) 
	{
		Velocity = FVector::ZeroVector;
	}
}


FVector AVehicle::GetAirResistance()
{
	return - Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient;
}


FVector AVehicle::GetRollingResistance()
{
	// F = M * g
	float Gravity = -GetWorld()->GetGravityZ() / 100;
	float NormalForce = Mass * Gravity;
	float RollingResistance = NormalForce * RollingResistanceCoefficient;

	return -Velocity.GetSafeNormal() * RollingResistance;
}

// Called to bind functionality to input
void AVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVehicle::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVehicle::MoveRight);
}

void AVehicle::MoveForward(float XAxis)
{
	//if (GEngine)
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Moving Forward"));
	//Velocity = GetActorForwardVector() * 20 * Axis;
	Throttle = XAxis;

} 

void AVehicle::MoveRight(float YAxis)
{

	SteeringAngle = YAxis;
}