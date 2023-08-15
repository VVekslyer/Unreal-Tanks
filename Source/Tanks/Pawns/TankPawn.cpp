// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


ATankPawn::ATankPawn()
{
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArmComp->SetupAttachment(RootComponent);

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
    PlayerControllerRef = Cast<APlayerController>(GetController());
}


void ATankPawn::HandleDestruction()
{
    Super::HandleDestruction();
    
    bIsPlayerAlive = false;

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

bool ATankPawn::GetIsPlayerAlive()
{
    return bIsPlayerAlive;
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
 
    Rotate(); // Rotate the tank if the player is hovering mouse
    Move(); // Move the tank if the player is moving via WASD

    if (PlayerControllerRef)
    {
        FHitResult TraceHitResult;
        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
        FVector HitLocation = TraceHitResult.ImpactPoint;

        RotateTurret(HitLocation);
    }
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ATankPawn::CalculateMoveInput); // Move the tank if the player is moving via WASD
    PlayerInputComponent->BindAxis("Turn", this, &ATankPawn::CalculateRotateInput); // Rotate the tank if the player is hovering mouse
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATankPawn::Fire); // Fire the tank if the player presses the left mouse button
}


void ATankPawn::CalculateMoveInput(float Value)
{ // Calculate the direction to move the tank
    float MoveAmount = Value * MoveSpeed * GetWorld()->DeltaTimeSeconds;
    MoveDirection = FVector(MoveAmount, 0, 0);
}


void ATankPawn::CalculateRotateInput(float Value)
{ // Calculate the direction to rotate the tank
    float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator Rotation = FRotator(0, RotateAmount, 0);
    RotationDirection = FQuat(Rotation);
}


void ATankPawn::Move()
{ // Move the tank
    AddActorLocalOffset(MoveDirection, true); // MoveDirection is a FVector of where the player wants to move the tank
}


void ATankPawn::Rotate()
{ // Rotate the tank
    AddActorLocalRotation(RotationDirection, true); // RotationDirection is a FQuat of where the player wants to rotate the tank
} // FQuat is a quaternion class that is used to store rotation information.