// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "DummyMaster.h"
#include "Mech_CombatCharacter.h"
#include "Components/SphereComponent.h"

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

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CarriedBombMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	USphereComponent* BombRadius;
	FTimerHandle ExplodeTimer;

public:
	ASpiderBomb();
	virtual void PostInitializeComponents() override;
	void ArmAndDestroy();
	void ExplodeAndDestroy();
	UFUNCTION()
    void OnBombRadiusBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
    		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBombRadiusEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
