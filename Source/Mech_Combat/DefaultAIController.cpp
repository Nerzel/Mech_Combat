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
        ADummyMaster* DummyMasterPossessed;

        DummyMasterPossessed = Cast<ADummyMaster>(PossessedPawn);
        UE_LOG(LogTemp, Warning, TEXT("OBJECTIF ATTEINT %s"), *Result.ToString());

        if (Cast<ADummyMaster>(PossessedPawn)->bIsChasing) {

            if (Result.IsSuccess()) {
                DummyMasterPossessed->bIsPlayerLocked = true;
                DummyMasterPossessed->PawnSensing->SensingInterval = -1.f;

                if (PossessedPawn->IsA<ASpiderBomb>()) {
                    // Cast<ASpiderBomb>(PossessedPawn)->ArmAndDestroy();
                }

            } else if (Result.IsFailure() && Result.Code != EPathFollowingResult::Aborted) {
                DummyMasterPossessed->bIsChasing = false;
                DummyMasterPossessed->bIsPlayerLocked = false;
                DummyMasterPossessed->PawnSensing->SensingInterval = 0.5f;
                GetWorldTimerManager().SetTimer(this->RoamTimer, DummyMasterPossessed,
                                                &ADummyMaster::RoamToRandomLocation, 3.f, false);
            }

        } else {
            GetWorldTimerManager().SetTimer(this->RoamTimer, DummyMasterPossessed,
                                            &ADummyMaster::RoamToRandomLocation, 3.f, false);
        }

    }

}
