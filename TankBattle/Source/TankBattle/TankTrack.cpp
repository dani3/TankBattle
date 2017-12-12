#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: Throttle applied: %f"), *Name, Throttle);

	Throttle = FMath::Clamp(Throttle, -1.f, 1.f);
}




