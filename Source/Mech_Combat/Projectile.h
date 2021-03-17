// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Projectile.generated.h"

UCLASS()
class MECH_COMBAT_API AProjectile : public AActor {

	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float LifeTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UParticleSystem* ExplosionParticle;

private:
	FTimerHandle DestroyTimer;

public:	
	// Sets default values for this actor's properties
	AProjectile();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult& SweepResult);
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
