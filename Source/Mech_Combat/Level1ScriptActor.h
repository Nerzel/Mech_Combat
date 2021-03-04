// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Mech_CombatGameMode.h"
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

public:
	ALevel1ScriptActor();

private:
	virtual void BeginPlay() override;
	
};
