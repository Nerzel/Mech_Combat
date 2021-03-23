// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/NewWaveWidget.h"

#include "Mech_CombatGameMode.generated.h"

class AMech_CombatCharacter;

UCLASS(minimalapi)
class AMech_CombatGameMode : public AGameModeBase {

	GENERATED_BODY()

public:
	int RemainingMinutes;
	int RemainingSeconds;
	int WaveNumber;
	int NumberOfBots;
	int MaxBots;
	int NumberOfKills;
	int ReplenishHealthCost;
	int ReplenishStaminahCost;
	int HealthUpgradeCost;
	int StaminaUpgradeCost;
	int SpeedUpgradeCost;
	int DamageUpgradeCost;
	int WhirlwindUpgradeCost;
	int HelicopterUpgradeCost;
	int LeapUpgradeCost;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=HUD)
	TSubclassOf<UNewWaveWidget> DefaultNewWaveWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UNewWaveWidget* NewWaveWidget;

private:
	FTimerHandle SecondIncreaseTimer;
	FTimerHandle NewWaveWidgetTimer;
	UPROPERTY(VisibleInstanceOnly)
	AMech_CombatCharacter* PlayerCharacter;

public:
	AMech_CombatGameMode();
	virtual void StartPlay() override;
	void IncreaseTimer();
	void TriggerNextWave();
	void ModifyNumberOfBots(const int Delta);

private:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};

