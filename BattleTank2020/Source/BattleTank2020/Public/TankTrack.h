// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK2020_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Set a throttle between -1 and 1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle, bool IsTurning);

	UTankTrack();
private:

	/* Tank weight = 40 Tonnes and acceleration = 1G.
	 * Remember that the acceleraion is in cm/s^2 = 400,000 Newtons
	 */
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000; // Max force per track, in Newtons

	//UPROPERTY(EditDefaultsOnly)
	//float ForceLocationOffsetScalar = 20.f;
};
