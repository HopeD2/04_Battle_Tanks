// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Public/TankAimingComponent.h"
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

	if (!ensure(PlayerControlledTank && AIControlledTank)) { return; }
	// Move towards the player.
	MoveToActor(PlayerControlledTank, AccRadius);

	// Aim towards the player.
	UTankAimingComponent *AimingComponent = AIControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		AimingComponent->AimAt(PlayerControlledTank->GetActorLocation());
	}
			
	// Fire if Ready
	AimingComponent->Fire();
}
