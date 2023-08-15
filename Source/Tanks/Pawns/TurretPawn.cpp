// Fill out your copyright notice in the Description page of Project Settings.

#include "TurretPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TankPawn.h"

// spawn function
void ATurretPawn::BeginPlay()
{
    // Call the parent class's BeginPlay function
    Super::BeginPlay();

    // Get a pointer to the world object by calling GetWorld()
    GetWorld()->GetTimerManager().SetTimer(
        FireRateTimerHandle,
        this, // Pass a pointer to this object as the second argument to specify the object that owns the timer
        &ATurretPawn::CheckFireCondition, // Pass a pointer to the CheckFireCondition function as the third argument to specify the function to call when the timer fires
        FireRate, // specify the time interval between timer firings
        true // Pass true as the fifth argument to specify that the timer should loop and fire repeatedly
    );


    // Set the PlayerPawn reference to the player pawn in the game world
    PlayerPawn = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATurretPawn::HandleDestruction()
{
    Super::HandleDestruction();

    Destroy();
}

// The Tick function is called every frame
void ATurretPawn::Tick(float DeltaTime)
{
    // Call the parent class's Tick function
    Super::Tick(DeltaTime);

    // Return early if the player pawn is not valid or if it is out of range
    if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange) { return; }

    // Rotate the turret to face the player pawn's location
    RotateTurret(PlayerPawn->GetActorLocation());
}

// The CheckFireCondition function checks if the turret should fire
void ATurretPawn::CheckFireCondition()
{
    // Return early if the player pawn is not valid or if it is not alive
    if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive()) { return; }

    // Fire if the player pawn is within range
    if (ReturnDistanceToPlayer() <= FireRange)
    {
        Fire();
    }
}

// The ReturnDistanceToPlayer function returns the distance between the turret and the player pawn
float ATurretPawn::ReturnDistanceToPlayer()
{
    // Return 0 if the player pawn is not valid
    if (!PlayerPawn) { return 0.f; }

    // Return the distance between the player pawn and the turret
    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
// FVector is a 3D vector class that is used to store position, direction and scale information.