// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Mech_CombatGameMode.generated.h"

UCLASS(minimalapi)
class AMech_CombatGameMode : public AGameModeBase {

	GENERATED_BODY()

public:
	int RemainingMinutes;
	int RemainingSeconds;
	int WaveNumber;
	int NomberOfBots;
	int MaxBots;

private:
	FTimerHandle SecondIncreaseTimer;

public:
	AMech_CombatGameMode();
	virtual void StartPlay();
	void IncreaseTimer();

};

