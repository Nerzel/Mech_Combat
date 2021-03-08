// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "ShopMenuWidget.generated.h"

class AMech_CombatGameMode;
class AMech_CombatCharacter;
/**
 * 
 */
UCLASS()
class MECH_COMBAT_API UShopMenuWidget : public UUserWidget {

	GENERATED_BODY()

public:
	UShopMenuWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentTimeFragments;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ReplenishHealthCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ReplenishStaminaCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HealthUpgradeCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* StaminaUpgradeCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SpeedUpgradeCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* DamageUpgradeCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* MaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CurrentDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ReplenishHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ReplenishStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* UpgradeMaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* UpgradeMaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* UpgradeSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* UpgradeDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* StaminaBar;

private:
	UPROPERTY(VisibleInstanceOnly)
	AMech_CombatCharacter* Character;
	UPROPERTY(VisibleInstanceOnly)
	AMech_CombatGameMode* GameMode;
	FNumberFormattingOptions FormatingOptions2Ints;
	FNumberFormattingOptions FormatingOptions3Ints;

public:
	UFUNCTION()
	void OnReplishHealthClick();
	UFUNCTION()
	void OnReplishStaminaClick();
	UFUNCTION()
    void OnUpgradeHealthClick();
	UFUNCTION()
    void OnUpgradeStaminaClick();
	UFUNCTION()
    void OnUpgradeSpeedClick();
	UFUNCTION()
    void OnUpgradeDamageClick();

};
