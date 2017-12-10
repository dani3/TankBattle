#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;

UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UTankBarrel * Barrel);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Aim at the location given
	void AimAt(FVector HitLocation) const;

protected:
	UTankAimingComponent * TankAimingComponent = nullptr;

private:
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000.f;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
