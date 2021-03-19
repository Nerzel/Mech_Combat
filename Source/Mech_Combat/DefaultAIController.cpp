// Copyright Nerzel. All Rights Reserved.


#include "DefaultAIController.h"

#include "SpiderBomb.h"

ADefaultAIController::ADefaultAIController() {

}

void ADefaultAIController::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    Super::EndPlay(EndPlayReason);

    GetWorldTimerManager().ClearTimer(this->RoamTimer);
}


void ADefaultAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) {
    Super::OnMoveCompleted(RequestID, Result);

    APawn* PossessedPawn = GetPawn();

    if (PossessedPawn->IsA<ADummyMaster>()) {
        if (Cast<ADummyMaster>(PossessedPawn)->bIsChasing) {
            if (Result.IsSuccess()) {
                Cast<ADummyMaster>(PossessedPawn)->bIsChasing = false;
                if (PossessedPawn->IsA<ASpiderBomb>()) {
                    Cast<ASpiderBomb>(PossessedPawn)->ArmAndDestroy();
                }
            } else if (Result.IsFailure()) {
                Cast<ADummyMaster>(PossessedPawn)->bIsChasing = false;
                GetWorldTimerManager().SetTimer(this->RoamTimer, Cast<ADummyMaster>(PossessedPawn), &ADummyMaster::RoamToRandomLocation, 3.f, false);
            }
        } else {
            GetWorldTimerManager().SetTimer(this->RoamTimer, Cast<ADummyMaster>(PossessedPawn), &ADummyMaster::RoamToRandomLocation, 3.f, false);
        }
    }
}
