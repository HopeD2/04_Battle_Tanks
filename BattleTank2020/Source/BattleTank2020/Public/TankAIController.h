// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK2020_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AccRadius = 8000; // How close the AI tank should be from player.

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
