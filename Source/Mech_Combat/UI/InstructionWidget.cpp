// Copyright Nerzel. All Rights Reserved.


#include "InstructionWidget.h"

#include "Mech_Combat/MainMenuGameMode.h"

UInstructionWidget::UInstructionWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
}

void UInstructionWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (this->ResetButton) {
		this->ResetButton->OnClicked.AddDynamic(this, &UInstructionWidget::OnResetButtonClick);
	}
}

void UInstructionWidget::OnResetButtonClick() {
	this->RemoveFromViewport();
	Cast<AMainMenuGameMode>(GetWorld()->GetAuthGameMode())->MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
}
