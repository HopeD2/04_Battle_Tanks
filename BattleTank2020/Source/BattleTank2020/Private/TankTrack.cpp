// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() {
	
}

void UTankTrack::SetThrottle(float Throttle, bool IsTurning)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s Throttle value : %f"), *GetName(), Throttle);

	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent *TankRootAsPrimitive = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRootAsPrimitive->AddForceAtLocation(ForceApplied, ForceLocation);
}
