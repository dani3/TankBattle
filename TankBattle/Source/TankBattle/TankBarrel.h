#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/*
 * TankBarrel is used to elevate the barrel with a 
 * maximum speed and maximum and minimum degrees of elevation.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed, +1 is max up movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegrees = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevationDegrees = 0.f;
};
