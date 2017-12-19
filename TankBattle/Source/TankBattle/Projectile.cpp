#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "Public/TimerManager.h"

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
	ExplosionForce =
		CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));

	SetRootComponent(CollisionMesh);

	CollisionMesh->SetNotifyRigidBodyCollision(true);

	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

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
	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::DestroyProjectile, DestroyDelay);
}

void AProjectile::DestroyProjectile()
{
	this->Destroy();
}

