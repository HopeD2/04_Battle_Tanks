// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK2020_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector WorldSpaceAim);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel *BarrelToSet, UTankTurret * TurretToSet);

	UFUNCTION(BlueprintCallable)
	bool Fire();

	EFiringStatus GetFiringState() const;

	UFUNCTION(BlueprintCallable)
	int GetAmmoCount() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = Setup)
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	void MoveBarrel(FVector AimDirection);

	bool IsBarrelMoving();

	// TODO : Make this 4000
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 10000.f; // Launch Speed 100,000 = 1000 m/s, as resolution is in cm

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = Firing)
	float ReloadTime = 3; //seconds

	double TimeOfLastReload = 0;

	UTankBarrel *Barrel = nullptr;

	UTankTurret *Turret = nullptr;

	FVector CurrentAimDirection = FVector(0);

	unsigned int AmmoCount = 10;
};
