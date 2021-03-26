#include "DefaultCharacterHUDWidget.h"


#include "Kismet/GameplayStatics.h"
#include "Mech_Combat/Mech_CombatCharacter.h"

UDefaultCharacterHUDWidget::UDefaultCharacterHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
}

void UDefaultCharacterHUDWidget::NativeConstruct() {
    Super::NativeConstruct();

    this->Character = Cast<AMech_CombatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
    this->FormatingOptions.MinimumIntegralDigits = 2;
    this->FormatingOptions.MaximumIntegralDigits = 2;
    this->IconMap = new TMap<UImage*, FSpecialAttackIcon*>();

    this->FillTextures(this->WirlwindIcon, this->WirlwindActiveIcon, this->WirlwindInactiveIcon, 3);
    this->FillTextures(this->HelicopterIcon, this->HelicopterActiveIcon, this->HelicopterInactiveIcon, 2);
    this->FillTextures(this->LeapIcon, this->LeapActiveIcon, this->LeapInactiveIcon, 2);
}

void UDefaultCharacterHUDWidget::FillTextures(UImage* ImageWidget, UTexture2D* ActiveTexture, UTexture2D* InactiveTexture, int LimiteValue) {
    FSpecialAttackIcon* SpecialAttackIcon;

    SpecialAttackIcon = new FSpecialAttackIcon();
    SpecialAttackIcon->ActiveIcon = ActiveTexture;
    SpecialAttackIcon->InactiveIcon = InactiveTexture;
    SpecialAttackIcon->LmiteValue = LimiteValue;

    this->IconMap->Add(ImageWidget, SpecialAttackIcon);
}

void UDefaultCharacterHUDWidget::SetHUDIcon() {
    if (this->WirlwindIcon && this->HelicopterIcon && this->LeapIcon) {
        for (TTuple<UImage*, FSpecialAttackIcon*>& Elem : *this->IconMap) {
            if (Elem.Key && this->Character->AttackEnergy >= Elem.Value->LmiteValue) {
                Elem.Key->SetBrushFromTexture(Elem.Value->ActiveIcon);
            } else {
                Elem.Key->SetBrushFromTexture(Elem.Value->InactiveIcon);
            }
        }
    }
}

void UDefaultCharacterHUDWidget::UpdateWaveNumber(const int NewWaveNumber) {
    if (this->WaveNumber) {
        this->WaveNumber->SetText(FText::AsNumber(NewWaveNumber, &this->FormatingOptions));
    }
}

void UDefaultCharacterHUDWidget::UpdateTimer(const int Minutes, const int Seconds) {
    if (this->MinuteTextBlock && this->SecondTextBlock) {
        this->MinuteTextBlock->SetText(FText::AsNumber(Minutes, &this->FormatingOptions));
        this->SecondTextBlock->SetText(FText::AsNumber(Seconds, &this->FormatingOptions));
    }
}

void UDefaultCharacterHUDWidget::UpdateNumberOfEnemies(const int NewNumberOfEnemies) {
    if (this->NumberOfEnemies) {
        this->NumberOfEnemies->SetText(FText::AsNumber(NewNumberOfEnemies, &this->FormatingOptions));
    }
}
