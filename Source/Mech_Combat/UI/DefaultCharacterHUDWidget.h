#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "DefaultCharacterHUDWidget.generated.h"

class AMech_CombatCharacter;
UCLASS()
class MECH_COMBAT_API UDefaultCharacterHUDWidget : public UUserWidget {

    GENERATED_BODY()

private:
    AMech_CombatCharacter* Character;

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

};
