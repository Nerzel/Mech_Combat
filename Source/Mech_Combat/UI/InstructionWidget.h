// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "InstructionWidget.generated.h"

/**
 * 
 */
UCLASS()
class MECH_COMBAT_API UInstructionWidget : public UUserWidget {

	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ResetButton;

public:
	UInstructionWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnResetButtonClick();
	
};
