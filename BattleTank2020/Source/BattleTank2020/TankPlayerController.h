// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last header

/**
 * 
 */
class UTankAimingComponent;

UCLASS()
class BATTLETANK2020_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATankPlayerController();

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent* ACompRef);
private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Move the tank barrel to fire a shot where the crosshair intersects
	// with the world.
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector &HitLocation) const;

	bool GetLookDirection(FVector2D &ScreenLocation, FVector &WorldDirection) const;

	bool GetLookHitLocation(FVector &HitLocation, FVector LookDirections) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange;
};
