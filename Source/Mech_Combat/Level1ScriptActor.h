// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Mech_CombatGameMode.h"
#include "Spawner.h"
#include "Engine/LevelScriptActor.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes)
	TSubclassOf<ASpiderBomb> DefaultSpiderBombClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes)
	TSubclassOf<ASpiderTurret> DefaultSpiderTurretClass;

private:
	bool EnnemyTypeFlag;
	FTimerHandle SpawnTimer;
	FTimerDelegate SpawnTimerDelegate;

public:
	ALevel1ScriptActor();

private:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
	void SpawnBots(TArray<ASpawner*> Spawners);
	UFUNCTION()
	void SpawnBotByClass(TArray<ASpawner*> Spawners);
	
};
