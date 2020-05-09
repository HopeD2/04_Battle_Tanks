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
	AActor *AIControlledActor = GetPawn();

	if (!ensure(PlayerControlledTank && AIControlledActor)) { return; }
	// Move towards the player.
	MoveToActor(PlayerControlledTank, AccRadius);

	// Aim towards the player.
	UTankAimingComponent *AimingComponent = AIControlledActor->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		AimingComponent->AimAt(PlayerControlledTank->GetActorLocation());
	}

	if (AimingComponent->GetFiringState() == EFiringStatus::Locked) {
		AimingComponent->Fire();
	}
}
