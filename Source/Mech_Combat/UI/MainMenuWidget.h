// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "InstructionWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MECH_COMBAT_API UMainMenuWidget : public UUserWidget {

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* StartGameButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ExitGameButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* InstructionButton;
	UPROPERTY(EditDefaultsOnly, Category=HUD)
	TSubclassOf<UInstructionWidget> DefaultInstructionWidgetClass;

public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	UFUNCTION()
    void OnStartGameButtonClick();
	UFUNCTION()
    void OnExitGameButtonClick();
	UFUNCTION()
    void OnInstructionButtonClick();
	
};
