// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Tank.h"


ATankPlayerController::ATankPlayerController() {
	CrossHairXLocation = 0.5;
	CrossHairYLocation = 0.33333;
	LineTraceRange = 100000.f;
}

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController::BeginPlay() is called"));

	ATank *ControlledTank = GetControlledTank();
	
	if (ControlledTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Tank name is : %s"),*ControlledTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player ControlledTank is null"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("Hit location : %s"), *HitLocation.ToString());
		//If it hits landscape
		//Tell controlled tank to aim at this point
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	// Get CrossHair location on screen in pixel co-ords.
	int32 ViewPortXSize, ViewPortYSize;
	GetViewportSize(ViewPortXSize, ViewPortYSize);
	
	FVector2D ScreenLocation = FVector2D(ViewPortXSize * CrossHairXLocation, ViewPortYSize* CrossHairYLocation);
	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//RayCast at crosshair location
		if (GetLookHitLocation(HitLocation,LookDirection)) {
			//UE_LOG(LogTemp, Warning, TEXT("Hitting Location : %s"), *HitLocation.ToString());
			GetControlledTank()->AimAt(HitLocation);
		}
	}
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D &ScreenLocation, FVector &LookDirection) const
{
	FVector WorldLocation;

	// De-project screen location of cross hair to world location/direction
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation, // This is the Camera's location, not necessary here
		LookDirection);// Direction in which you are looking. Most probably a Unit vector
}

bool ATankPlayerController::GetLookHitLocation(FVector & HitLocation, FVector LookDirection) const
{
	FHitResult HitResult;

	FVector LineTraceStart;
	FRotator Rotation;
	
	GetPlayerViewPoint(LineTraceStart, Rotation);
	//LineTraceStart = PlayerCameraManager->GetCameraLocation();

	FVector LineTraceEnd = LineTraceStart + LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		LineTraceStart,
		LineTraceEnd,
		ECC_Visibility)
		)
	{
	/*	DrawDebugLine(
		GetWorld(),
		LineTraceStart,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		10.0f
		);*/

		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0);
	return false;
}