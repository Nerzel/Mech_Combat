// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "Mech_CombatGameMode.h"
#include "Spawner.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/TriggerBox.h"

#include "Level1ScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class MECH_COMBAT_API ALevel1ScriptActor : public ALevelScriptActor {

	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AMech_CombatGameMode* GameMode;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Classes)
	TSubclassOf<ASpiderBomb> DefaultSpiderBombClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Classes)
	TSubclassOf<ASpiderTurret> DefaultSpiderTurretClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Sequences)
	ULevelSequence* DoorsLevelSequence;

private:
	bool EnnemyTypeFlag;
	FTimerHandle SpawnTimer;
	FTimerHandle NewWaveCheckTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes, meta=(AllowPrivateAccess = "true"))
	TArray<ASpawner*> Spawners;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes, meta=(AllowPrivateAccess = "true"))
	ATriggerBox* DoorsTriggerBox;
	UPROPERTY(VisibleInstanceOnly)
	ULevelSequencePlayer* DoorsSequencePlayer;

public:
	ALevel1ScriptActor();

private:
	virtual void BeginPlay() override;
	void SpawnBots();
	void SpawnBotByClass();
	void CheckNewWave();
	UFUNCTION()
	void OnDoorsTriggerBoxBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnDoorsTriggerBoxEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
};
