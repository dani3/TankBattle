#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed, +1 is max up movement
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 30.f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0.f;
};
