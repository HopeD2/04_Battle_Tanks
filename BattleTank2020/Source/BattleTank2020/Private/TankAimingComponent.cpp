// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// So that first fire is after initial reload
	TimeOfLastReload = FPlatformTime::Seconds();
	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if ((FPlatformTime::Seconds() - TimeOfLastReload) < ReloadTime) 
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringStatus = EFiringStatus::Aiming;
	}
	else {
		FiringStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim)
{
	if (!ensure(Barrel)) { return; }

	FVector LaunchVelocity(0);
	//This is our start location for the Projectile.
	//A socket on the barrel.
	FVector BarrelLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			LaunchVelocity,
			BarrelLocation,
			WorldSpaceAim,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		)
	) 
	{
		// Calculate the Out launch velocity
		CurrentAimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrel(CurrentAimDirection);
	}
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) {
		return;
	}

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	// Work out difference between current barrel rotation and aim direction
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator RotationDifference = AimDirection.Rotation() - BarrelRotation;

	//UE_LOG(LogTemp, Warning, TEXT("BarrelRotationDifference : %s"), *RotationDifference.ToString());
	
	if (!ensure(Barrel)) { return; }
	Barrel->Elevate(RotationDifference.Pitch);

	if (!ensure(Turret)) { return; }	
	Turret->RotateTurret(RotationDifference.GetNormalized().Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return (!CurrentAimDirection.Equals(Barrel->GetForwardVector(),0.01));
}

bool UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return false; }

	if (FiringStatus != EFiringStatus::Reloading) {
		AProjectile *Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		TimeOfLastReload = FPlatformTime::Seconds();
		return true;
	}
	else {
		return false;
	}
}
