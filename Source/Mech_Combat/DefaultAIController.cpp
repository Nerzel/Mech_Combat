// Copyright Nerzel. All Rights Reserved.


#include "DefaultAIController.h"

#include "SpiderBomb.h"

ADefaultAIController::ADefaultAIController() {

}

void ADefaultAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) {
    Super::OnMoveCompleted(RequestID, Result);

    APawn* PossessedPawn = GetPawn();

    if (PossessedPawn->IsA<ADummyMaster>()) {
        if (Cast<ADummyMaster>(PossessedPawn)->bIsChasing) {
            if (Result.IsSuccess()) {
                if (PossessedPawn->IsA<ASpiderBomb>()) {
                    Cast<ASpiderBomb>(PossessedPawn)->ArmAndDestroy();
                }
            }
        } else {
            GetWorldTimerManager().SetTimer(this->RoamTimer, Cast<ADummyMaster>(PossessedPawn), &ADummyMaster::RoamToRandomLocation, 5.f, false);
        }
    }
}
