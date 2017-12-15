#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

/*
 * Class used to represent a projectile.
 */
UCLASS()
class TANKBATTLE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Launch projectile to a given speed
	void LaunchProjectile(float Speed);

protected:
	UProjectileMovementComponent * ProjectileMovementComponent = nullptr;
};
