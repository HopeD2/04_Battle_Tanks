// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Math/UnrealMathUtility.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the barrel by right amount this frame
	// Give a max elevation speed and the frame time
	// RelativeSpeed is calculated based on the difference between 
	// Destination position (which is the crosshair position) and the current barrel position.
	// MaxDegreesPerSecond will allow the designer to change how fast the barrel can move
	// Multiplying this by DeltaTimeSeconds will allow to have same results even if frames fluctuate.
	float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange; // New Elevation in degrees

	float ClampedElevationValue = FMath::Clamp(RawNewElevation, MinAllowedElevation, MaxAllowedElevation);
	
	SetRelativeRotation(FRotator(ClampedElevationValue, 0, 0));
}
