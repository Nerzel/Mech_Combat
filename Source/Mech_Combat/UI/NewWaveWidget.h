// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "NewWaveWidget.generated.h"

/**
 * 
 */
UCLASS()
class MECH_COMBAT_API UNewWaveWidget : public UUserWidget {

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentWaveNumber;

private:
	FNumberFormattingOptions FormatingOptions;

public:
	UNewWaveWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeOnInitialized() override;
	void SetCurrentWaveNumberText(float WaveNumber);
	
};
