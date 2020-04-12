// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//TODO : Find sensible default
	LaunchSpeed = 10000.f; // Launch Speed 100,000 = 1000 m/s, as resolution is in cm
	ReloadTime = 3;
	TimeOfLastReload = FPlatformTime::Seconds();
	Barrel = nullptr;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

bool ATank::Fire()
{
	bool bIsTankReloaded = (FPlatformTime::Seconds() - TimeOfLastReload) > ReloadTime;

	if (Barrel && bIsTankReloaded) {
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

void ATank::AimAt(FVector HitLocation)
{
	if (TankAimingComponent) {
		TankAimingComponent->AimAt(HitLocation,LaunchSpeed);
	}
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

