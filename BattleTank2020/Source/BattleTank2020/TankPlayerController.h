// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last header

/**
 * 
 */
UCLASS()
class BATTLETANK2020_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

	// Move the tank barrel to fire a shot where the crosshair intersects
	// with the world.
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector &HitLocation) const;

	bool GetLookDirection(FVector2D &ScreenLocation, FVector &WorldDirection) const;

	bool GetLookHitLocation(FVector &HitLocation, FVector LookDirections) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation;

	UPROPERTY(EditAnywhere)
	float LineTraceRange;
};
