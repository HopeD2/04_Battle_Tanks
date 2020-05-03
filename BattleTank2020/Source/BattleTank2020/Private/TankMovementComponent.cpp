// Copyright GhantaGaming Ltd.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack * LeftTrack, UTankTrack * RightTrack)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }

	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTakeTurn(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("%s Throw is : %f"), *GetOwner()->GetName(), Throw);
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super as default functionality is getting replaced.
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float Throw = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMoveForward(Throw);

	FVector Turn = FVector::CrossProduct(AIForwardIntention, TankForward);
	IntendTakeTurn(-Turn.Z);
	//UE_LOG(LogTemp, Warning, TEXT("Tank Name : %s, Move Velocity : %s"), *GetOwner()->GetName(), *MoveVelocityNormalized.ToString());
}
