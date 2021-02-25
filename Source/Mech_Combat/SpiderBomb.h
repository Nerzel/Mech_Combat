// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DummyMaster.h"
#include "Mech_CombatCharacter.h"
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

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CarriedBombMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), Category = AI)
	UPawnSensingComponent* PawnSensing;
	UPROPERTY(VisibleInstanceOnly)
	AMech_CombatCharacter* Character;
	FTimerHandle ExplodeTimer;

public:
	ASpiderBomb();
	UFUNCTION()
	void OnSeePawn(APawn *OtherPAwn);
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	void ArmAndDestroy();
	void ExplodeAndDestroy();
};
