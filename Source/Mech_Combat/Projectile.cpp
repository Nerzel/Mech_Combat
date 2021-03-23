 // Copyright Nerzel. All Rights Reserved.


#include "Projectile.h"

#include "Mech_CombatCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

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

void AProjectile::PostInitializeComponents() {
	Super::PostInitializeComponents();

	if (this->Mesh) {
		this->Mesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
	}
}

void AProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearTimer(this->DestroyTimer);
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

void AProjectile::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult) {
	if (OtherActor && OtherActor->IsA<AMech_CombatCharacter>()) {
		AMech_CombatCharacter* Character;

		Character = Cast<AMech_CombatCharacter>(OtherActor);
		Character->Health -= 0.05f;
		Character->UpdateHealthBar();

		if (Character->Health <= 0.f) {
			Character->Death();
		}

		if (this->ExplosionParticle) {
			UGameplayStatics::SpawnEmitterAtLocation(this, this->ExplosionParticle, GetActorLocation());
		}
		Destroy();
	}
}
