 // Copyright Nerzel. All Rights Reserved.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile() {
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneComponent"));
	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    this->Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	this->Mesh->SetCollisionProfileName(TEXT("OverlapAll"));
	this->Mesh->SetNotifyRigidBodyCollision(true);
	this->ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovementComponent"));
	this->ProjectileMovementComponent->InitialSpeed = 5000.f;
	this->ProjectileMovementComponent->MaxSpeed = 5000.f,
	this->ProjectileMovementComponent->Velocity = FVector(5000.f, 1.f, 1.f);

	PrimaryActorTick.bCanEverTick = false;
	this->LifeTime = 2.5f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
	FTimerDelegate Delegate;

	Super::BeginPlay();

	Delegate.BindLambda([this] { Destroy(); });

	GetWorldTimerManager().SetTimer(DestroyTimer, Delegate, this->LifeTime, false);
}

// Called every frame
void AProjectile::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

