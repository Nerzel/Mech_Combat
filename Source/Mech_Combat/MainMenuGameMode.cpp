// Copyright Nerzel. All Rights Reserved.


#include "MainMenuGameMode.h"

AMainMenuGameMode::AMainMenuGameMode() {
	static ConstructorHelpers::FClassFinder<UMainMenuWidget> MainMenuBPClass(TEXT("/Game/MechCombat/Blueprints/UI/MainMenuWidget_BP"));
	if (MainMenuBPClass.Class != NULL) {
		this->DefaultMainMenuWidgetClass = MainMenuBPClass.Class;
	}

	DefaultPawnClass = nullptr;
	HUDClass = nullptr;
}

void AMainMenuGameMode::StartPlay() {
	Super::StartPlay();

	if (this->DefaultMainMenuWidgetClass) {
		CreateWidget<UMainMenuWidget>(GetWorld(), this->DefaultMainMenuWidgetClass)->AddToViewport();
	}

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
}
