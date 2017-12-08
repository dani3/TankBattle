#include "TankPlayerController.h"
#include "Engine/World.h"

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}




