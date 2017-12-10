#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::SetBarrel(UTankBarrel * Barrel)
{
	this->Barrel = Barrel;
}

void UTankAimingComponent::SetTurret(UTankTurret * Turret)
{
	this->Turret = Turret;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLauchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(
			this
		  , OutLauchVelocity
		  , StartLocation
		  , HitLocation
		  , LaunchSpeed
		  , false
		  , 0
		  , 0
		  , ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLauchVelocity.GetSafeNormal();

		// Move barrel
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

