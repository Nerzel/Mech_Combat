#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Mech_Combat/Mech_CombatGameMode.h"

#include "DefaultCharacterHUDWidget.generated.h"

class AMech_CombatCharacter;
UCLASS()
class MECH_COMBAT_API UDefaultCharacterHUDWidget : public UUserWidget {

    GENERATED_BODY()

private:
    AMech_CombatCharacter* Character;
    AMech_CombatGameMode* GameMode;
    FNumberFormattingOptions FormatingOptions;
    TMap<FString, UTexture2D*>* IconMap;

public:
    UDefaultCharacterHUDWidget(const FObjectInitializer& ObjectInitializer);
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
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

private:
    void SetHUDIcon(UImage* ImageWidget, const int LimitValue, const FString IconName);
    void FillTextures(const FString TextureName, const FString TexturePath);

};
