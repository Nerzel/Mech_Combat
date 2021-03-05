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
}

void ALevel1ScriptActor::SpawnBots(TArray<ASpawner*> Spawners) {
	SpawnTimerDelegate.BindUFunction(this, FName("SpawnBotByClass"), Spawners);
	GetWorld()->GetTimerManager().SetTimer(this->SpawnTimer, SpawnTimerDelegate, 3.f, true);
}

void ALevel1ScriptActor::SpawnBotByClass(TArray<ASpawner*> Spawners) {

	if (this->EnnemyTypeFlag) {
		Spawners[FMath::RandRange(0, Spawners.Num() - 1)]->SpawnBot(DefaultSpiderBombClass);
	} else {
		Spawners[FMath::RandRange(0, Spawners.Num() - 1)]->SpawnBot(DefaultSpiderTurretClass);
	}

	if (this->GameMode->NumberOfBots >= this->GameMode->MaxBots) {
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	}

	this->EnnemyTypeFlag = !this->EnnemyTypeFlag;
}
