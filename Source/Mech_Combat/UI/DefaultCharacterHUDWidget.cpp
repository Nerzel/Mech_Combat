#include "DefaultCharacterHUDWidget.h"


#include "Kismet/GameplayStatics.h"
#include "Mech_Combat/Mech_CombatCharacter.h"

UDefaultCharacterHUDWidget::UDefaultCharacterHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
}

void UDefaultCharacterHUDWidget::NativeConstruct() {
    Super::NativeConstruct();

    this->Character = Cast<AMech_CombatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
    this->GameMode = (AMech_CombatGameMode*)GetWorld()->GetAuthGameMode();
    this->FormatingOptions.MinimumIntegralDigits = 2;
    this->FormatingOptions.MaximumIntegralDigits = 2;
}

void UDefaultCharacterHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (this->HealthBar) {
        this->HealthBar->SetPercent(Character->Health);
    }

    if (this->StaminaBar) {
        this->StaminaBar->SetPercent(Character->Stamina);
    }

    if (this->AttackEnergyBar) {
        this->AttackEnergyBar->SetPercent(Character->AttackEnergy / 12.0f);
    }

    if(this->MinuteTextBlock && this->SecondTextBlock) {
        this->MinuteTextBlock->SetText(FText::AsNumber(GameMode->RemainingMinutes, &this->FormatingOptions));
        this->SecondTextBlock->SetText(FText::AsNumber(GameMode->RemainingSeconds, &this->FormatingOptions));
    }
}
