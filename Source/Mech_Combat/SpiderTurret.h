// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DummyMaster.h"
#include "SpiderTurret.generated.h"

/**
 * 
 */
UCLASS()
class MECH_COMBAT_API ASpiderTurret : public ADummyMaster {

	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsShooting;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CarriedTurretMesh;

public:
	ASpiderTurret();
	
};
