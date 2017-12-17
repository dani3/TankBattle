#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = 
		CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	LaunchBlast = 
		CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	ProjectileMovementComponent = 
		CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ImpactBlast = 
		CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));

	SetRootComponent(CollisionMesh);

	CollisionMesh->SetNotifyRigidBodyCollision(true);

	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovementComponent->bAutoActivate = false;
	ImpactBlast->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Launch projectile to a given speed
void AProjectile::LaunchProjectile(float Speed)
{
	if (!ensure(ProjectileMovementComponent)) { return; }

	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
}

void AProjectile::OnHit(
	UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ImpactBlast->Activate();
}

