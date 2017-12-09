#include "TankPlayerController.h"

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller possesing: %s"), *(ControlledTank->GetName()));
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *(HitLocation.ToString()));

		// Get world location of linetrace through the crosshair
		// If it hits something
			// Aim at this point
	}
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

// Get world location of linetrace through the crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector WorldDirection;
	if (GetLookDirection(ScreenLocation, WorldDirection))
	{
		// Line-trace along that look direction, and see what we hit (up to max range)
	}

	return false;
}

// "De-project" the screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & WorldDirection) const
{
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(
				ScreenLocation.X, ScreenLocation.Y, WorldLocation, WorldDirection);
}


