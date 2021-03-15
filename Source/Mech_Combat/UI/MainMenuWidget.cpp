// Copyright Nerzel. All Rights Reserved.


#include "MainMenuWidget.h"

#include "Kismet/GameplayStatics.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
}

void UMainMenuWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (this->StartGameButton) {
		this->StartGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartGameButtonClick);
	}

	if (this->ExitGameButton) {
		this->ExitGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitGameButtonClick);
	}
}

void UMainMenuWidget::OnStartGameButtonClick() {
	UGameplayStatics::OpenLevel(GetWorld(), FName("Level1"));
}

void UMainMenuWidget::OnExitGameButtonClick() {
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}