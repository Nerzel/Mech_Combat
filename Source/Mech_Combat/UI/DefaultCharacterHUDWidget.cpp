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
    this->IconMap = new TMap<FString, UTexture2D*>();

    this->FillTextures("Whirlwind", "/Game/MechCombat/UserInterface/Whirlwind.Whirlwind");
    this->FillTextures("WhirlwindDark", "/Game/MechCombat/UserInterface/WhirlwindDark.WhirlwindDark");
    this->FillTextures("Helicopter", "/Game/MechCombat/UserInterface/Helicopter.Helicopter");
    this->FillTextures("HelicopterDark", "/Game/MechCombat/UserInterface/HelicopterDark.HelicopterDark");
    this->FillTextures("Leap", "/Game/MechCombat/UserInterface/Leap.Leap");
    this->FillTextures("LeapDark", "/Game/MechCombat/UserInterface/LeapDark.LeapDark");
}

void UDefaultCharacterHUDWidget::FillTextures(const FString TextureName, const FString TexturePath) {
    UTexture2D* Texture;

    Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *TexturePath));

    if (Texture) {
        this->IconMap->Add(TextureName, Texture);
    }
}

void UDefaultCharacterHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (this->HealthBar) {
        this->HealthBar->SetPercent(this->Character->Health / this->Character->MaxHealth);
    }

    if (this->StaminaBar) {
        this->StaminaBar->SetPercent(this->Character->Stamina / this->Character->MaxStamina);
    }

    if (this->AttackEnergyBar) {
        this->AttackEnergyBar->SetPercent(this->Character->AttackEnergy / 12.0f);
    }

    if (this->MinuteTextBlock && this->SecondTextBlock) {
        this->MinuteTextBlock->SetText(FText::AsNumber(this->GameMode->RemainingMinutes, &this->FormatingOptions));
        this->SecondTextBlock->SetText(FText::AsNumber(this->GameMode->RemainingSeconds, &this->FormatingOptions));
    }

    if (this->WirlwindIcon) {
        this->SetHUDIcon(this->WirlwindIcon, 3, "Whirlwind");
    }

    if (this->HelicopterIcon) {
        this->SetHUDIcon(this->HelicopterIcon, 2, "Helicopter");
    }

    if (this->LeapIcon) {
        this->SetHUDIcon(this->LeapIcon, 2, "Leap");
    }

    if (this->TimeFragmentNumber) {
        this->TimeFragmentNumber->SetText(FText::AsNumber(this->Character->TimeFragments, &this->FormatingOptions));
    }

    if (this->WaveNumber) {
        this->WaveNumber->SetText(FText::AsNumber(this->GameMode->WaveNumber, &this->FormatingOptions));
    }

    if (this->NumberOfEnemies) {
        this->NumberOfEnemies->SetText(FText::AsNumber(this->GameMode->NumberOfBots, &this->FormatingOptions));
    }
}

void UDefaultCharacterHUDWidget::SetHUDIcon(UImage* ImageWidget, const int LimitValue, const FString IconName) {
    if (this->Character->AttackEnergy >= LimitValue) {
        ImageWidget->SetBrushFromTexture(*this->IconMap->Find(IconName));
    } else {
        ImageWidget->SetBrushFromTexture(*this->IconMap->Find(IconName + "Dark"));
    }
}
