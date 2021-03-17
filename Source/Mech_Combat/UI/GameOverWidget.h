// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* WaveNumber;

public:
	UGameOverWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	void SetWaveNumberText(const int Value);
	UFUNCTION()
	void RestartGame();
	UFUNCTION()
	void ExitGame();
};
