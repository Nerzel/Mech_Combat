// Copyright Nerzel. All Rights Reserved.


#include "DefaultAIController.h"

#include "SpiderBomb.h"

ADefaultAIController::ADefaultAIController() {

}

void ADefaultAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) {
    Super::OnMoveCompleted(RequestID, Result);
    if (Result.IsSuccess()) {
        APawn* PossessedPawn = GetPawn();

        if (PossessedPawn->IsA<ASpiderBomb>()) {
            Cast<ASpiderBomb>(PossessedPawn)->ArmAndDestroy();;
        }
    }
}
