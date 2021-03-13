// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "SpiderBomb.h"
#include "SpiderTurret.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class MECH_COMBAT_API ASpawner : public AActor {

	GENERATED_BODY()

private:
	UPROPERTY(VisibleInstanceOnly)
	AMech_CombatGameMode* GameMode;

public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SpawnBot(UClass* Class);

};
