#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack * LeftTrack, UTankTrack * RightTrack)
{
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);

	// TODO prevent double speed
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	RightTrack->SetThrottle(-Throw);
	LeftTrack->SetThrottle(Throw);

	// TODO prevent double speed
}




