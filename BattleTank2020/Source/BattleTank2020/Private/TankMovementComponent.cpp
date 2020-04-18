// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack * LeftTrack, UTankTrack * RightTrack)
{
	if (!LeftTrack || !RightTrack) { return; }

	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack && !RightTrack) { return; }

	LeftTrack->SetThrottle(Throw, false);
	RightTrack->SetThrottle(Throw, false);
}

void UTankMovementComponent::IntendTakeTurn(float Throw)
{
	if (!LeftTrack && !RightTrack) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("%s Throw is : %f"), *GetOwner()->GetName(), Throw);
	LeftTrack->SetThrottle(-Throw, true);
	RightTrack->SetThrottle(Throw, true);
}
