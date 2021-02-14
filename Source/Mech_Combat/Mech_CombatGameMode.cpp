// Copyright Epic Games, Inc. All Rights Reserved.

#include "Mech_CombatGameMode.h"
#include "UObject/ConstructorHelpers.h"

AMech_CombatGameMode::AMech_CombatGameMode() {
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	this->RemainingMinutes = 0;
	this->RemainingSeconds = 0;
}

void AMech_CombatGameMode::StartPlay() {
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(SecondIncreaseTimer, this, &AMech_CombatGameMode::IncreaseTimer, 1.0f, true);
}

void AMech_CombatGameMode::IncreaseTimer() {
	if (this->RemainingSeconds == 59) {
		this->RemainingSeconds = 0;
		this->RemainingMinutes++;
	} else {
		this->RemainingSeconds++;
	}
}
