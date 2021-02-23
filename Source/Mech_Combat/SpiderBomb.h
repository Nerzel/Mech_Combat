// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DummyMaster.h"
#include "SpiderBomb.generated.h"

/**
 * 
 */
UCLASS()
class MECH_COMBAT_API ASpiderBomb : public ADummyMaster {

	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsArmed;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* CarriedBombMesh;

public:
	ASpiderBomb();
};
