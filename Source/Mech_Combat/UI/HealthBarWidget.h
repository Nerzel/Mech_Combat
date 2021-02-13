#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBarWidget.generated.h"

class AMech_CombatCharacter;
UCLASS()
class MECH_COMBAT_API UHealthBarWidget : public UUserWidget {

    GENERATED_BODY()

private:
    AMech_CombatCharacter* Character;

public:
    UHealthBarWidget(const FObjectInitializer& ObjectInitializer);

    virtual void NativeConstruct() override;

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UProgressBar* HealthBar;

};
