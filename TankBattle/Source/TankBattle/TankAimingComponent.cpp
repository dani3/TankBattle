#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastTimeFire = FPlatformTime::Seconds();
}

// Called every frame
void UTankAimingComponent::TickComponent(
	float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - ReloadTimeInSeconds) < LastTimeFire)
	{
		AimingState = EAimingState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		AimingState = EAimingState::Aiming;
	}
	else
	{
		AimingState = EAimingState::Locked;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel * Barrel, UTankTurret * Turret)
{
	this->Barrel = Barrel;
	this->Turret = Turret;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

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
		AimDirection = OutLauchVelocity.GetSafeNormal();

		// Move barrel
		MoveBarrelTowards(AimDirection);
	}
}

EAimingState UTankAimingComponent::GetAimingState() const
{
	return AimingState;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

void UTankAimingComponent::Fire()
{
	if (RoundsLeft == 0)
	{
		AimingState = EAimingState::OutOfAmmo;
		return;
	}

	if (AimingState != EAimingState::Reloading)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		// Spawn a projectile at the socket location on the barrel
		auto SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
		auto SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketLocation, SocketRotation);

		Projectile->LaunchProjectile(LaunchSpeed);

		LastTimeFire = FPlatformTime::Seconds();

		RoundsLeft--;
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	// Work-out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	// Always rotate the shortest way
	if (FMath::Abs(DeltaRotator.Yaw) > 180.f)
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}

	Barrel->Elevate(DeltaRotator.Pitch);
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) { return false; }

	auto BarrelCurrentAimLocation = Barrel->GetForwardVector();

	return !(BarrelCurrentAimLocation.Equals(AimDirection, 0.01f));
}

