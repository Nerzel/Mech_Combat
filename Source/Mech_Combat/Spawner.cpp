// Copyright Nerzel. All Rights Reserved.


#include "Spawner.h"

#include "Mech_CombatGameMode.h"
#include "SpiderBomb.h"
#include "SpiderTurret.h"

// Sets default values
ASpawner::ASpawner() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay() {
	Super::BeginPlay();
	this->GameMode = Cast<AMech_CombatGameMode>(GetWorld()->GetAuthGameMode());
}

void ASpawner::SpawnBot(UClass* Class) {
	GetWorld()->SpawnActor<ADummyMaster>(Class, this->GetTransform());
	this->GameMode->ModifyNumberOfBots(1);
}

