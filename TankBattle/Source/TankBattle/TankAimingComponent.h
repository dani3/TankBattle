#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EAimingState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TANKBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrel(UTankBarrel * Barrel);
	void SetTurret(UTankTurret * Turret);

	void AimAt(FVector HitLocation, float LaunchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EAimingState AimingState = EAimingState::Reloading;

private:
	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
};
