#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "DefaultCharacterHUDWidget.generated.h"

class AMech_CombatCharacter;

struct FSpecialAttackIcon {
    UTexture2D* ActiveIcon;
    UTexture2D* InactiveIcon;
    int LmiteValue;
};

UCLASS()
class MECH_COMBAT_API UDefaultCharacterHUDWidget : public UUserWidget {

    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UProgressBar* HealthBar;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UProgressBar* StaminaBar;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UProgressBar* AttackEnergyBar;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* MinuteTextBlock;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* SecondTextBlock;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UImage* WirlwindIcon;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UImage* HelicopterIcon;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UImage* LeapIcon;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* TimeFragmentNumber;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* WaveNumber;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UTextBlock* NumberOfEnemies;
    FNumberFormattingOptions FormatingOptions;

private:
    UPROPERTY(VisibleInstanceOnly)
    AMech_CombatCharacter* Character;
    TMap<UImage*, FSpecialAttackIcon>* IconMap;

public:
    UDefaultCharacterHUDWidget(const FObjectInitializer& ObjectInitializer);
    virtual void NativeConstruct() override;
    void SetHUDIcon();
    void UpdateWaveNumber(const int NewWaveNumber);
    void UpdateTimer(const int Minutes, const int Seconds);
    void UpdateNumberOfEnemies(const int NewNumberOfEnemies);

private:
    void FillTextures(UImage* ImageWidget, const FString ActiveTexturePath, const FString InactiveTexturePath, int LimiteValue);

};
