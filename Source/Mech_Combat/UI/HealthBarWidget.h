#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBarWidget.generated.h"

UCLASS()
class MECH_COMBAT_API UHealthBarWidget : public UUserWidget {

    GENERATED_BODY()

public:
    UHealthBarWidget(const FObjectInitializer& ObjectInitializer);

    void UpdateHealthBar(float HealthValue);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UProgressBar* HealthBar;

};
