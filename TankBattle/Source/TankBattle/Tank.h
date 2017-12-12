#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankTrack;
class AProjectile;

UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UTankBarrel * Barrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurret(UTankTurret * Turret);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetLeftTrack(UTankTrack * Track);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetRightTrack(UTankTrack * Track);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Aim at the location given
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

protected:
	UTankAimingComponent * TankAimingComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBluePrint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 8000.f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.f;

	UTankBarrel * Barrel;
	double LastTimeFire = 0;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
