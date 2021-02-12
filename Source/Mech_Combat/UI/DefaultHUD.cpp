#include "DefaultHUD.h"

ADefaultHUD::ADefaultHUD() {
}

void ADefaultHUD::BeginPlay() {
    Super::BeginPlay();

    if (HealthBarWidgetClass) {
        this->HealthBarWidget = CreateWidget<UHealthBarWidget>(GetWorld(), HealthBarWidgetClass, FName(TEXT("HealthBarWidget")));
    }
}

void ADefaultHUD::UdpateHealthBar(float HealthValue) {
    if (this->HealthBarWidget) {
        this->HealthBarWidget->UpdateHealthBar(HealthValue);
    }
}
