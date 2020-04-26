// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack() {
	
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent *> Children;
	GetChildrenComponents(true, Children);

	TArray<ASprungWheel*> Wheels;

	for (USceneComponent* Child : Children)
	{
		auto SpawnPoint = Cast<USpawnPoint>(Child);
		if (!SpawnPoint) { continue; }

		AActor* SpawnedActor = SpawnPoint->GetSpawnedActor();

		auto SprungWheel = Cast<ASprungWheel>(SpawnedActor);
		if (!SprungWheel) { continue; }
		Wheels.Add(SprungWheel);
	}
	
	return Wheels;
}

void UTankTrack::SetThrottle(float Throttle)
{
	float ForceApplied = Throttle * TrackMaxDrivingForce;
	TArray<ASprungWheel*> Wheels = GetWheels();
//	UE_LOG(LogTemp, Warning, TEXT("Wheels.Num() : %d"), Wheels.Num());

	float ForceAppliedPerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForceAppliedPerWheel);
	}
}
