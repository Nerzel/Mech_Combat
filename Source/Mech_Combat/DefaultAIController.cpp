// Copyright Nerzel. All Rights Reserved.


#include "DefaultAIController.h"

#include "SpiderBomb.h"

ADefaultAIController::ADefaultAIController() {

}

void ADefaultAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) {
    Super::OnMoveCompleted(RequestID, Result);

    APawn* PossessedPawn = GetPawn();

    if (PossessedPawn->IsA<ASpiderBomb>()) {
        ASpiderBomb* SpiderBomb;

        SpiderBomb = Cast<ASpiderBomb>(PossessedPawn);

        if (SpiderBomb->bIsChasing) {
            if (Result.IsSuccess()) {
                SpiderBomb->ArmAndDestroy();
            }
        } else {
            GetWorldTimerManager().SetTimer(this->RoamTimer, SpiderBomb, &ASpiderBomb::RoamToRandomLocation, 5.f, false);
        }
    }
}
