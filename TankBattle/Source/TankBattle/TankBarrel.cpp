#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame rate
	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f) * MaxVerticalDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation, 0.f, 0.f));
}




