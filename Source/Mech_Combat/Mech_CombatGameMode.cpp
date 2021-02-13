// Copyright Epic Games, Inc. All Rights Reserved.

#include "Mech_CombatGameMode.h"
#include "UObject/ConstructorHelpers.h"

AMech_CombatGameMode::AMech_CombatGameMode() {

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<AActor> HUDClassBP(TEXT("/Game/MechCombat/Blueprints/UI/DefaultHUD_BP"));
	if (HUDClassBP.Class != NULL) {
		HUDClass = HUDClassBP.Class;
	}

}
