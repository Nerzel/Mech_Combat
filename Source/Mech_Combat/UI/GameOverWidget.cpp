// Copyright Nerzel. All Rights Reserved.


#include "GameOverWidget.h"

#include "Kismet/GameplayStatics.h"

UGameOverWidget::UGameOverWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
}

void UGameOverWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (this->RestartButton) {
		this->RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::RestartGame);
	}

	if (this->ExitGameButton) {
		this->ExitGameButton->OnClicked.AddDynamic(this, &UGameOverWidget::ExitGame);
	}
}


void UGameOverWidget::SetWaveNumberText(const int Value) {
	FNumberFormattingOptions FormatingOptions;

	FormatingOptions.MinimumIntegralDigits = 2;

	if (this->WaveNumber) {
		this->WaveNumber->SetText(FText::AsNumber(Value, &FormatingOptions));
	}
}

void UGameOverWidget::RestartGame() {
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("RestartLevel");
}

void UGameOverWidget::ExitGame() {
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenuLevel"));
}
