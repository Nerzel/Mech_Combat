// Copyright Nerzel. All Rights Reserved.


#include "Level1ScriptActor.h"

ALevel1ScriptActor::ALevel1ScriptActor() {
	static ConstructorHelpers::FClassFinder<ASpiderBomb> SpiderBombBPClass(TEXT("/Game/MechCombat/Blueprints/SpiderBomb_BP"));
	if (SpiderBombBPClass.Class != NULL) {
		DefaultSpiderBombClass = SpiderBombBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<ASpiderTurret> SpiderTurretBPClass(TEXT("/Game/MechCombat/Blueprints/SpiderTurret_BP"));
	if (SpiderTurretBPClass.Class != NULL) {
		DefaultSpiderTurretClass = SpiderTurretBPClass.Class;
	}

	this->EnnemyTypeFlag = true;
}

void ALevel1ScriptActor::BeginPlay() {
	Super::BeginPlay();

	this->GameMode = Cast<AMech_CombatGameMode>(GetWorld()->GetAuthGameMode());
	SpawnBots();
}

void ALevel1ScriptActor::SpawnBots() {

	if (this->Spawners.Num()) {
		GetWorld()->GetTimerManager().SetTimer(this->SpawnTimer, this, &ALevel1ScriptActor::SpawnBotByClass, 3.f, true);
	}

}

void ALevel1ScriptActor::SpawnBotByClass() {

	if (this->EnnemyTypeFlag) {
		Spawners[FMath::RandRange(0, Spawners.Num() - 1)]->SpawnBot(DefaultSpiderBombClass);
	} else {
		Spawners[FMath::RandRange(0, Spawners.Num() - 1)]->SpawnBot(DefaultSpiderTurretClass);
	}

	if (this->GameMode->NumberOfBots + this->GameMode->NumberOfKills == this->GameMode->MaxBots) {
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	}

	if (!this->NewWaveCheckTimer.IsValid()) {
		GetWorld()->GetTimerManager().SetTimer(this->NewWaveCheckTimer, this, &ALevel1ScriptActor::CheckNewWave, 2.f, true);
	}

	this->EnnemyTypeFlag = !this->EnnemyTypeFlag;
}

void ALevel1ScriptActor::CheckNewWave() {

	if (this->GameMode->NumberOfKills == this->GameMode->MaxBots) {
		GetWorld()->GetTimerManager().ClearTimer(this->NewWaveCheckTimer);
		this->GameMode->NumberOfKills = 0;
		this->GameMode->TriggerNextWave();
		SpawnBots();
	}

}
