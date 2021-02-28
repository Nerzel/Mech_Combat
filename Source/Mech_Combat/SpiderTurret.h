// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DummyMaster.h"
#include "Projectile.h"

#include "SpiderTurret.generated.h"

/**
 * 
 */
UCLASS()
class MECH_COMBAT_API ASpiderTurret : public ADummyMaster {

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes)
	TSubclassOf<AProjectile> DefaultProjectileClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsShooting;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ShootRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ShootRange;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CarriedTurretMesh;
	FTimerHandle ShootingTimer;

public:
	ASpiderTurret();
	virtual void BeginPlay() override;
	void Shoot();
    void OnSeePawn(APawn *OtherPAwn) override;
	
};
