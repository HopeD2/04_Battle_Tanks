// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank *AiControlledTank = GetControlledTank();

	if (AiControlledTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("AI tank : %s reporting for duty"), *AiControlledTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AiControlledTank = nullptr"));
	}

	ATank *PlayerControlledTank = GetPlayerTank();

	if (AiControlledTank != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Player tank at AI controller: %s Spotted!"), *PlayerControlledTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank at AI controller = nullptr"));
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	APawn *PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}
	else {
		return Cast<ATank>(PlayerPawn);
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank *PlayerControlledTank = GetPlayerTank();
	if (PlayerControlledTank) {
		// Move towards the player.

		// Aim towards the player.
		GetControlledTank()->AimAt(PlayerControlledTank->GetActorLocation());

		// Fire if Ready
	}
}
