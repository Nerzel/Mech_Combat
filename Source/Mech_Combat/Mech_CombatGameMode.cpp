// Copyright Epic Games, Inc. All Rights Reserved.

#include "Mech_CombatGameMode.h"
#include "UObject/ConstructorHelpers.h"

AMech_CombatGameMode::AMech_CombatGameMode() {
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UNewWaveWidget> NewWaveWidgetBPClass(TEXT("/Game/MechCombat/Blueprints/UI/NewWaveWidget_BP"));
	if (NewWaveWidgetBPClass.Class != NULL) {
		DefaultNewWaveWidgetClass = NewWaveWidgetBPClass.Class;
	}

	this->RemainingMinutes = 0;
	this->RemainingSeconds = 0;
	this->WaveNumber = 0;
	this->NumberOfBots = 0;
	this->MaxBots = 0;
	this->NumberOfKills = 0;
	this->ReplenishHealthCost = 10;
	this->ReplenishStaminahCost = 5;
	this->HealthUpgradeCost = 5;
	this->StaminaUpgradeCost = 5;
	this->SpeedUpgradeCost = 10;
	this->DamageUpgradeCost = 5;
	this->WhirlwindUpgradeCost = 7;
	this->HelicopterUpgradeCost = 7;
	this->LeapUpgradeCost = 7;
}

void AMech_CombatGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}


void AMech_CombatGameMode::StartPlay() {
	Super::StartPlay();

	this->TriggerNextWave();

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

void AMech_CombatGameMode::TriggerNextWave() {
	this->WaveNumber++;
	this->NumberOfKills = 0;
	this->MaxBots = FMath::RoundToInt(FMath::Exp(this->WaveNumber/6.f) * 5.f - 1);
	if (this->DefaultNewWaveWidgetClass) {
		FTimerDelegate Delegate;

		this->NewWaveWidget = CreateWidget<UNewWaveWidget>(GetWorld(), this->DefaultNewWaveWidgetClass, FName(TEXT("NewWaveWidget")));
		this->NewWaveWidget->SetCurrentWaveNumberText(this->WaveNumber);
		this->NewWaveWidget->AddToViewport();

		Delegate.BindLambda([this] { this->NewWaveWidget->RemoveFromViewport(); });
		GetWorldTimerManager().SetTimer(NewWaveWidgetTimer, Delegate, 2.0f, false);
	}
}
