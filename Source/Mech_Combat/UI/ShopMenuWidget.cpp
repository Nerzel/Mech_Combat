// Copyright Nerzel. All Rights Reserved.


#include "ShopMenuWidget.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Mech_Combat/Mech_CombatCharacter.h"

UShopMenuWidget::UShopMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
}

void UShopMenuWidget::NativeConstruct() {
	Super::NativeConstruct();

	this->Character = Cast<AMech_CombatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	this->GameMode = (AMech_CombatGameMode*)GetWorld()->GetAuthGameMode();
	this->FormatingOptions2Ints.MinimumIntegralDigits = 2;
	this->FormatingOptions3Ints.MinimumIntegralDigits = 3;

	if (this->ReplenishHealth) {
		this->ReplenishHealth->OnClicked.AddDynamic(this, &UShopMenuWidget::OnReplishHealthClick);
	}

	if (this->ReplenishStamina) {
		this->ReplenishStamina->OnClicked.AddDynamic(this, &UShopMenuWidget::OnReplishStaminaClick);
	}

	if (this->UpgradeMaxHealth) {
		this->UpgradeMaxHealth->OnClicked.AddDynamic(this, &UShopMenuWidget::OnUpgradeHealthClick);
	}

	if (this->UpgradeMaxStamina) {
		this->UpgradeMaxStamina->OnClicked.AddDynamic(this, &UShopMenuWidget::OnUpgradeStaminaClick);
	}

	if (this->UpgradeSpeed) {
		this->UpgradeSpeed->OnClicked.AddDynamic(this, &UShopMenuWidget::OnUpgradeSpeedClick);
	}

	if (this->UpgradeDamage) {
		this->UpgradeDamage->OnClicked.AddDynamic(this, &UShopMenuWidget::OnUpgradeDamageClick);
	}

	if (this->UpgradeWhirlwind) {
		this->UpgradeWhirlwind->OnClicked.AddDynamic(this, &UShopMenuWidget::OnUpgradeWhirlwindClick);
	}

	if (this->UpgradeHelicopter) {
		this->UpgradeHelicopter->OnClicked.AddDynamic(this, &UShopMenuWidget::OnUpgradeHelicopterClick);
	}

	if (this->UpgradeLeap) {
		this->UpgradeLeap->OnClicked.AddDynamic(this, &UShopMenuWidget::OnUpgradeLeapClick);
	}

	if (this->ReplenishHealthCost) {
		this->ReplenishHealthCost->SetText(FText::AsNumber(this->GameMode->ReplenishHealthCost, &this->FormatingOptions2Ints));
	}

	if (this->ReplenishStaminaCost) {
		this->ReplenishStaminaCost->SetText(FText::AsNumber(this->GameMode->ReplenishStaminahCost, &this->FormatingOptions2Ints));
	}
}

void UShopMenuWidget::OnReplishHealthClick() {
	if (this->Character->TimeFragments >= this->GameMode->ReplenishHealthCost && this->Character->Health < this->Character->MaxHealth) {
		this->Character->Health = this->Character->MaxHealth;
		this->Character->TimeFragments -= this->GameMode->ReplenishHealthCost;
		this->Character->UpdateHUDTimeFragments();
		this->UpdateTimeFragments();
		this->Character->UpdateHealthBar();
	}
}

void UShopMenuWidget::OnReplishStaminaClick() {
	if (this->Character->TimeFragments >= this->GameMode->ReplenishStaminahCost && this->Character->Stamina < this->Character->MaxStamina) {
		this->Character->Stamina = this->Character->MaxStamina;
		this->Character->TimeFragments -= this->GameMode->ReplenishStaminahCost;
		this->Character->UpdateHUDTimeFragments();
		this->UpdateTimeFragments();
		this->Character->UpdateStaminaBar();
	}
}

void UShopMenuWidget::OnUpgradeHealthClick() {
	if (this->Character->TimeFragments >= this->GameMode->HealthUpgradeCost) {
		this->Character->MaxHealth *= 1.2f;
		this->Character->TimeFragments -= this->GameMode->HealthUpgradeCost;
		this->UpdateTimeFragments();
		this->Character->UpdateHUDTimeFragments();
		this->GameMode->HealthUpgradeCost *= 2;
		this->Character->UpdateHealthBar();
		this->UpdateMaxHealthText();
		this->UpdateHealthCost();
	}
}

void UShopMenuWidget::OnUpgradeStaminaClick() {
	if (this->Character->TimeFragments >= this->GameMode->StaminaUpgradeCost) {
		this->Character->MaxStamina *= 1.2f;
		this->Character->TimeFragments -= this->GameMode->StaminaUpgradeCost;
		this->UpdateTimeFragments();
		this->Character->UpdateHUDTimeFragments();
		this->GameMode->StaminaUpgradeCost *= 2;
		this->Character->AutoIncreaseStamina();
		this->Character->UpdateStaminaBar();
		this->UpdateMaxStaminaText();
		this->UpdateStaminaCost();
	}
}

void UShopMenuWidget::OnUpgradeSpeedClick() {
	if (this->Character->TimeFragments >= this->GameMode->SpeedUpgradeCost) {
		this->Character->MovementSpeed += 200;
		this->Character->GetCharacterMovement()->MaxWalkSpeed = this->Character->MovementSpeed;
		this->Character->TimeFragments -= this->GameMode->SpeedUpgradeCost;
		this->UpdateTimeFragments();
		this->Character->UpdateHUDTimeFragments();
		this->GameMode->SpeedUpgradeCost *= 2.5f;
		this->UpdateMaxSpeedText();
		this->UpdateSpeedCost();
	}
}

void UShopMenuWidget::OnUpgradeDamageClick() {
	if (this->Character->TimeFragments >= this->GameMode->DamageUpgradeCost) {
		this->Character->NormalDamage += 0.1f;
		this->Character->TimeFragments -= this->GameMode->DamageUpgradeCost;
		this->UpdateTimeFragments();
		this->Character->UpdateHUDTimeFragments();
		this->GameMode->DamageUpgradeCost *= 2;
		this->UpdateCurrentDamageText();
		this->UpdateDamageCost();
	}
}

void UShopMenuWidget::OnUpgradeWhirlwindClick() {
	if (this->Character->TimeFragments >= this->GameMode->WhirlwindUpgradeCost) {
		this->Character->WhirlwindDamage += 0.1f;
		this->Character->TimeFragments -= this->GameMode->WhirlwindUpgradeCost;
		this->UpdateTimeFragments();
		this->Character->UpdateHUDTimeFragments();
		this->GameMode->WhirlwindUpgradeCost *= 2;
		this->UpdateWhirlwindDamageText();
		this->UpdateWhirlwindCost();
	}
}

void UShopMenuWidget::OnUpgradeHelicopterClick() {
	if (this->Character->TimeFragments >= this->GameMode->HelicopterUpgradeCost) {
		this->Character->HelicopterDamage += 0.15f;
		this->Character->TimeFragments -= this->GameMode->HelicopterUpgradeCost;
		this->UpdateTimeFragments();
		this->Character->UpdateHUDTimeFragments();
		this->GameMode->HelicopterUpgradeCost *= 2;
		this->UpdateHelicopterDamageText();
		this->UpdateHelicopterCost();
	}
}

void UShopMenuWidget::OnUpgradeLeapClick() {
	if (this->Character->TimeFragments >= this->GameMode->LeapUpgradeCost) {
		this->Character->LeapDamage += 0.2f;
		this->Character->TimeFragments -= this->GameMode->LeapUpgradeCost;
		this->UpdateTimeFragments();
		this->Character->UpdateHUDTimeFragments();
		this->GameMode->LeapUpgradeCost *= 2;
		this->UpdateLeapDamageText();
		this->UpdateLeapCost();
	}
}

void UShopMenuWidget::UpdateTimeFragments() {
	if (this->CurrentTimeFragments) {
		this->CurrentTimeFragments->SetText(FText::AsNumber(this->Character->TimeFragments, &this->FormatingOptions3Ints));
	}
}

void UShopMenuWidget::UpdateHealthBar() {
	if (this->HealthBar) {
		this->HealthBar->SetPercent(this->Character->Health / this->Character->MaxHealth);
	}
}

void UShopMenuWidget::UpdateStaminaBar() {
	if (this->StaminaBar) {
		this->StaminaBar->SetPercent(this->Character->Stamina / this->Character->MaxStamina);
	}
}

void UShopMenuWidget::UpdateMaxHealthText() {
	if (this->MaxHealth) {
		this->MaxHealth->SetText(FText::AsPercent(this->Character->MaxHealth));
	}
}

void UShopMenuWidget::UpdateMaxStaminaText() {
	if (this->MaxStamina) {
		this->MaxStamina->SetText(FText::AsPercent(this->Character->MaxStamina));
	}
}

void UShopMenuWidget::UpdateMaxSpeedText() {
	if (this->MaxSpeed) {
		this->MaxSpeed->SetText(FText::AsPercent(static_cast<float>(this->Character->MovementSpeed) / static_cast<float>(this->Character->DefaultMovementSpeed)));
	}
}

void UShopMenuWidget::UpdateCurrentDamageText() {
	if (this->CurrentDamage) {
		this->CurrentDamage->SetText(FText::AsNumber(this->Character->NormalDamage * 100));
	}
}

void UShopMenuWidget::UpdateWhirlwindDamageText() {
	if (this->CurrentWhirlwindDamage) {
		this->CurrentWhirlwindDamage->SetText(FText::AsNumber(this->Character->WhirlwindDamage * 100));
	}
}

void UShopMenuWidget::UpdateHelicopterDamageText() {
	if (this->CurrentHelicopterDamage) {
		this->CurrentHelicopterDamage->SetText(FText::AsNumber(this->Character->HelicopterDamage * 100));
	}
}

void UShopMenuWidget::UpdateLeapDamageText() {
	if (this->CurrentLeapDamage) {
		this->CurrentLeapDamage->SetText(FText::AsNumber(this->Character->LeapDamage * 100));
	}
}

void UShopMenuWidget::UpdateHealthCost() {
	if (this->HealthUpgradeCost) {
		this->HealthUpgradeCost->SetText(FText::AsNumber(this->GameMode->HealthUpgradeCost, &this->FormatingOptions2Ints));
	}
}

void UShopMenuWidget::UpdateStaminaCost() {
	if (this->StaminaUpgradeCost) {
		this->StaminaUpgradeCost->SetText(FText::AsNumber(this->GameMode->StaminaUpgradeCost, &this->FormatingOptions2Ints));
	}
}

void UShopMenuWidget::UpdateSpeedCost() {
	if (this->SpeedUpgradeCost) {
		this->SpeedUpgradeCost->SetText(FText::AsNumber(this->GameMode->SpeedUpgradeCost, &this->FormatingOptions2Ints));
	}
}

void UShopMenuWidget::UpdateDamageCost() {
	if (this->DamageUpgradeCost) {
		this->DamageUpgradeCost->SetText(FText::AsNumber(this->GameMode->DamageUpgradeCost, &this->FormatingOptions2Ints));
	}
}

void UShopMenuWidget::UpdateWhirlwindCost() {
	if (this->WhirlwindUpgradeCost) {
		this->WhirlwindUpgradeCost->SetText(FText::AsNumber(this->GameMode->WhirlwindUpgradeCost, &this->FormatingOptions2Ints));
	}
}

void UShopMenuWidget::UpdateHelicopterCost() {
	if (this->HelicopterUpgradeCost) {
		this->HelicopterUpgradeCost->SetText(FText::AsNumber(this->GameMode->HelicopterUpgradeCost, &this->FormatingOptions2Ints));
	}
}

void UShopMenuWidget::UpdateLeapCost() {
	if (this->LeapUpgradeCost) {
		this->LeapUpgradeCost->SetText(FText::AsNumber(this->GameMode->LeapUpgradeCost, &this->FormatingOptions2Ints));
	}
}
