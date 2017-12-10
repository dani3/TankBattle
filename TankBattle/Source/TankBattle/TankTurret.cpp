#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Move the turret the right amount this frame
	// Given a max rotation speed, and the frame rate
	auto RotationChange = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Pitch + RotationChange;

	SetRelativeRotation(FRotator(0.f, Rotation, 0.f));
}




