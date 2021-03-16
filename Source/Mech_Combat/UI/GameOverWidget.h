// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class MECH_COMBAT_API UGameOverWidget : public UUserWidget {

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* RestartButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitGameButton;

public:
	UGameOverWidget(const FObjectInitializer& ObjectInitializer);
	
};
