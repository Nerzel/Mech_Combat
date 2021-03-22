// Copyright Nerzel. All Rights Reserved.


#include "MainMenuWidget.h"

#include "Kismet/GameplayStatics.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	static ConstructorHelpers::FClassFinder<UInstructionWidget> InstructionBPClass(TEXT("/Game/MechCombat/Blueprints/UI/InstructionWidget_BP"));
	if (InstructionBPClass.Class != NULL) {
		this->DefaultInstructionWidgetClass = InstructionBPClass.Class;
	}
}

void UMainMenuWidget::NativeConstruct() {
	Super::NativeConstruct();

	if (this->StartGameButton) {
		this->StartGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartGameButtonClick);
	}

	if (this->ExitGameButton) {
		this->ExitGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitGameButtonClick);
	}

	if (this->InstructionButton) {
		this->InstructionButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnInstructionButtonClick);
	}
}

void UMainMenuWidget::OnStartGameButtonClick() {
	UGameplayStatics::OpenLevel(GetWorld(), FName("Level1"));
}

void UMainMenuWidget::OnExitGameButtonClick() {
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

void UMainMenuWidget::OnInstructionButtonClick() {
	this->SetVisibility(ESlateVisibility::Hidden);
	CreateWidget<UInstructionWidget>(GetWorld(), this->DefaultInstructionWidgetClass)->AddToViewport();
}