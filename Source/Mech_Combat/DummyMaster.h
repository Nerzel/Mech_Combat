// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


#include "AIController.h"
#include "Mech_CombatCharacter.h"
#include "TimeFragment.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"

#include "DummyMaster.generated.h"

UCLASS(config=Game)
class ADummyMaster : public ACharacter {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes)
	TSubclassOf<ATimeFragment> DefaultCollectableClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsChasing;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float RoamingRadius;

protected:
	UParticleSystem* ExplosionParticle;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), Category = AI)
	UPawnSensingComponent* PawnSensing;
	UPROPERTY(VisibleInstanceOnly)
	AAIController* AIController;
	UPROPERTY(VisibleInstanceOnly)
	AMech_CombatCharacter* PlayerCharacter;

public:
	ADummyMaster();
    virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	UFUNCTION()
	virtual void OnSeePawn(APawn *OtherPAwn);
	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void RoamToRandomLocation();
};

