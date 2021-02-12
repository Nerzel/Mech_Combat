#pragma once
#include "HealthBarWidget.h"
#include "GameFramework/HUD.h"
#include "DefaultHUD.generated.h"

UCLASS()
class MECH_COMBAT_API ADefaultHUD : public AHUD {

    GENERATED_BODY()

public:
    ADefaultHUD();
    virtual void BeginPlay() override;
    UFUNCTION()
    void UdpateHealthBar(float HealthValue);
    UPROPERTY(EditDefaultsOnly, Category=Widgets)
    TSubclassOf<UHealthBarWidget> HealthBarWidgetClass;

private:
    UHealthBarWidget* HealthBarWidget;

};
