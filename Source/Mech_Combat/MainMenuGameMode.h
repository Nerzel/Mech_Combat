// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/MainMenuWidget.h"

#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MECH_COMBAT_API AMainMenuGameMode : public AGameModeBase {

	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category=HUD)
	TSubclassOf<UMainMenuWidget> DefaultMainMenuWidgetClass;

public:
	AMainMenuGameMode();
	virtual void StartPlay() override;
	
};
