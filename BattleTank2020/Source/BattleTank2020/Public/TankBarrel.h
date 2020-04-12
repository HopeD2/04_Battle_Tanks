// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK2020_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 5; // Use some default value

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxAllowedElevation = 35; //Degrees;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinAllowedElevation = 0; // Degrees;
};
