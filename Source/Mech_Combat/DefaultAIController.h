// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DefaultAIController.generated.h"

/**
 * 
 */
UCLASS()
class MECH_COMBAT_API ADefaultAIController : public AAIController {

	GENERATED_BODY()

public:
	ADefaultAIController();
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

private:
	FTimerHandle RoamTimer;

private:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
};
