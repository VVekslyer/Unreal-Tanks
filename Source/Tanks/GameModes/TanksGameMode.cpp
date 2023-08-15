// Fill out your copyright notice in the Description page of Project Settings.

#include "TanksGameMode.h"
#include "Tanks/Pawns/TankPawn.h"
#include "Tanks/Pawns/TurretPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Tanks/PlayerControllers/PlayerControllerBase.h"

// The BeginPlay function is called when the game starts or when spawned
void ATanksGameMode::BeginPlay()
{
    // Call the parent class's BeginPlay function
    Super::BeginPlay();

    // Handle the start of the game
    HandleGameStart();
}

// The ActorDied function is called when an actor dies
void ATanksGameMode::ActorDied(AActor* DeadActor)
{
    // Check if the dead actor is the player tank
    if (DeadActor == PlayerTank)
    {
        // Handle the player tank's destruction
        PlayerTank->HandleDestruction();
        // Indicate that the player lost
        HandleGameOver(false);

        // Disable player input if the player controller reference is valid
        if (PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);
        }
    }
    // Check if the dead actor is a turret pawn
    else if (ATurretPawn* DestroyedTurret = Cast<ATurretPawn>(DeadActor))
    {
        // Handle the destroyed turret's destruction
        DestroyedTurret->HandleDestruction();

        // Decrement the target turrets counter and check if it has reached 0
        if (--TargetTurrets == 0)
        {
            // Indicate that the player won
            HandleGameOver(true);
        }
    }
}

// The HandleGameStart function handles the start of the game
void ATanksGameMode::HandleGameStart()
{
    // Set the target turrets counter to the number of turrets in the level
    TargetTurrets = GetTurretsNum();
    // Set the player tank and player controller references
    PlayerTank = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

    // Call GameStart() which can be overridden in Blueprints.
    GameStart();

    // Check if PlayerControllerRef is valid.
    if (PlayerControllerRef) {
        // Disable player input.
        PlayerControllerRef->SetPlayerEnabledState(false);

        // Create a timer that will enable player input after StartDelay seconds.
        FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef,
            &APlayerControllerBase::SetPlayerEnabledState, true);

        GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
    }
}

// The HandleGameOver function handles the end of the game and takes a boolean argument indicating whether or not player won.
void ATanksGameMode::HandleGameOver(bool PlayerWon)
{
    // Call GameOver() which can be overridden in Blueprints.
    GameOver(PlayerWon);
}

// The GetTurretsNum function returns an int32 representing number of turrets in level.
int32 ATanksGameMode::GetTurretsNum()
{
    TArray<AActor*> TurretActors;

    // Get all actors of class ATurretPawn and store them in TurretActors array.
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurretPawn::StaticClass(), TurretActors);

    return TurretActors.Num(); // Return number of elements in TurretActors array.
}
