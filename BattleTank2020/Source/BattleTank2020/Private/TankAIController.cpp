// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank *PlayerControlledTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank *AIControlledTank = Cast<ATank>(GetPawn());

	if (PlayerControlledTank) {
		// Move towards the player.

		// Aim towards the player.
		AIControlledTank->AimAt(PlayerControlledTank->GetActorLocation());

		// Fire if Ready
		AIControlledTank->Fire();
	}
}
