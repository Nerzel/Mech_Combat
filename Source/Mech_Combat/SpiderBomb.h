// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "DummyMaster.h"
#include "Mech_CombatCharacter.h"
#include "Components/SphereComponent.h"
#include "Perception/PawnSensingComponent.h"

#include "SpiderBomb.generated.h"

/**
 * 
 */
UCLASS()
class MECH_COMBAT_API ASpiderBomb : public ADummyMaster {

	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsArmed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsPlayerInRadius;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float RoamingRadius;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsChasing;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CarriedBombMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), Category = AI)
	UPawnSensingComponent* PawnSensing;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	USphereComponent* BombRadius;
	UPROPERTY(VisibleInstanceOnly)
	AMech_CombatCharacter* Character;
	FTimerHandle ExplodeTimer;
	UPROPERTY(VisibleInstanceOnly)
	AAIController* AIController;

public:
	ASpiderBomb();
	UFUNCTION()
	void OnSeePawn(APawn *OtherPAwn);
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	void ArmAndDestroy();
	void ExplodeAndDestroy();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	void RoamToRandomLocation();
};
