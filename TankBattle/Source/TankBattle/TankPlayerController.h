#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/*
 * Responsible for helping the player aim.
 */
UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent * AimingComponentRef);

private:
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = .5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = .3f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	UFUNCTION()
	void OnTankDeath();

	virtual void SetPawn(APawn * InPawn) override;

	// Start the tank moving the barrel so that a shot would hit
	// where the crosshair intersects the world
	void AimTowardsCrosshair();
	// Get world location of linetrace through the crosshair
	// Return an OUT parameter, true if hits landscape
	bool GetSightRayHitLocation(FVector & OutHitLocation) const;
	// "De-project" the screen position of the crosshair to a world direction
	bool GetLookDirection(FVector2D ScreenLocation, FVector & WorldDirection) const;
	// Line-trace to get the world location where the camera is looking at.
	bool GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation) const;
};
