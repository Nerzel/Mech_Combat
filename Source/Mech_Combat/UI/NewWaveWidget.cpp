// Copyright Nerzel. All Rights Reserved.


#include "NewWaveWidget.h"

UNewWaveWidget::UNewWaveWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
}

void UNewWaveWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

	this->FormatingOptions.MinimumIntegralDigits = 2;
	this->FormatingOptions.MaximumIntegralDigits = 2;
}

void UNewWaveWidget::SetCurrentWaveNumberText(float WaveNumber) {
	this->CurrentWaveNumber->SetText(FText::AsNumber(WaveNumber, &this->FormatingOptions));
}