// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed) 
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	float NewRotation = RelativeRotation.Yaw + RotationChange;
//	UE_LOG(LogTemp, Warning, TEXT("Tank : %s Rotation Change : %f, RelativeRotation.Yaw : %f, NewRotation : %f"), *GetOwner()->GetName(),RotationChange,RelativeRotation.Yaw,NewRotation);

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}