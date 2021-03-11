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

void UShopMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (this->CurrentTimeFragments) {
		this->CurrentTimeFragments->SetText(FText::AsNumber(this->Character->TimeFragments, &this->FormatingOptions3Ints));
	}

	if (this->HealthBar) {
		this->HealthBar->SetPercent(Character->Health);
	}

	if (this->StaminaBar) {
		this->StaminaBar->SetPercent(Character->Stamina);
	}

	if (this->MaxHealth) {
		this->MaxHealth->SetText(FText::AsPercent(this->Character->MaxHealth));
	}

	if (this->MaxStamina) {
		this->MaxStamina->SetText(FText::AsPercent(this->Character->MaxStamina));
	}

	if (this->MaxSpeed) {
		this->MaxSpeed->SetText(FText::AsPercent(static_cast<float>(this->Character->MovementSpeed) / static_cast<float>(this->Character->DefaultMovementSpeed)));
	}

	if (this->CurrentDamage) {
		this->CurrentDamage->SetText(FText::AsNumber(this->Character->NormalDamage * 100));
	}

	if (this->CurrentWhirlwindDamage) {
		this->CurrentWhirlwindDamage->SetText(FText::AsNumber(this->Character->WhirlwindDamage * 100));
	}

	if (this->CurrentHelicopterDamage) {
		this->CurrentHelicopterDamage->SetText(FText::AsNumber(this->Character->HelicopterDamage * 100));
	}

	if (this->CurrentLeapDamage) {
		this->CurrentLeapDamage->SetText(FText::AsNumber(this->Character->LeapDamage * 100));
	}

	if (this->HealthUpgradeCost) {
		this->HealthUpgradeCost->SetText(FText::AsNumber(this->GameMode->HealthUpgradeCost, &this->FormatingOptions2Ints));
	}

	if (this->StaminaUpgradeCost) {
		this->StaminaUpgradeCost->SetText(FText::AsNumber(this->GameMode->StaminaUpgradeCost, &this->FormatingOptions2Ints));
	}

	if (this->SpeedUpgradeCost) {
		this->SpeedUpgradeCost->SetText(FText::AsNumber(this->GameMode->SpeedUpgradeCost, &this->FormatingOptions2Ints));
	}

	if (this->DamageUpgradeCost) {
		this->DamageUpgradeCost->SetText(FText::AsNumber(this->GameMode->DamageUpgradeCost, &this->FormatingOptions2Ints));
	}

	if (this->WhirlwindUpgradeCost) {
		this->WhirlwindUpgradeCost->SetText(FText::AsNumber(this->GameMode->WhirlwindUpgradeCost, &this->FormatingOptions2Ints));
	}

	if (this->HelicopterUpgradeCost) {
		this->HelicopterUpgradeCost->SetText(FText::AsNumber(this->GameMode->HelicopterUpgradeCost, &this->FormatingOptions2Ints));
	}

	if (this->LeapUpgradeCost) {
		this->LeapUpgradeCost->SetText(FText::AsNumber(this->GameMode->LeapUpgradeCost, &this->FormatingOptions2Ints));
	}
}

void UShopMenuWidget::OnReplishHealthClick() {
	if (this->Character->TimeFragments >= this->GameMode->ReplenishHealthCost && this->Character->Health < 1.f) {
		this->Character->Health = this->Character->MaxHealth;
		this->Character->TimeFragments -= this->GameMode->ReplenishHealthCost;
	}
}

void UShopMenuWidget::OnReplishStaminaClick() {
	if (this->Character->TimeFragments >= this->GameMode->ReplenishStaminahCost && this->Character->Stamina < 1.f) {
		this->Character->Stamina = this->Character->MaxStamina;
		this->Character->TimeFragments -= this->GameMode->ReplenishStaminahCost;
	}
}

void UShopMenuWidget::OnUpgradeHealthClick() {
	if (this->Character->TimeFragments >= this->GameMode->HealthUpgradeCost) {
		this->Character->MaxHealth *= 1.2f;
		this->Character->TimeFragments -= this->GameMode->HealthUpgradeCost;
		this->GameMode->HealthUpgradeCost *= 2;
	}
}

void UShopMenuWidget::OnUpgradeStaminaClick() {
	if (this->Character->TimeFragments >= this->GameMode->StaminaUpgradeCost) {
		this->Character->MaxStamina *= 1.2f;
		this->Character->TimeFragments -= this->GameMode->StaminaUpgradeCost;
		this->GameMode->StaminaUpgradeCost *= 2;
		this->Character->AutoIncreaseStamina();
	}
}

void UShopMenuWidget::OnUpgradeSpeedClick() {
	if (this->Character->TimeFragments >= this->GameMode->SpeedUpgradeCost) {
		this->Character->MovementSpeed += 200;
		this->Character->GetCharacterMovement()->MaxWalkSpeed = this->Character->MovementSpeed;
		this->Character->TimeFragments -= this->GameMode->SpeedUpgradeCost;
		this->GameMode->SpeedUpgradeCost *= 2.5f;
	}
}

void UShopMenuWidget::OnUpgradeDamageClick() {
	if (this->Character->TimeFragments >= this->GameMode->DamageUpgradeCost) {
		this->Character->NormalDamage += 0.1f;
		this->Character->TimeFragments -= this->GameMode->DamageUpgradeCost;
		this->GameMode->DamageUpgradeCost *= 2;
	}
}

void UShopMenuWidget::OnUpgradeWhirlwindClick() {
	if (this->Character->TimeFragments >= this->GameMode->WhirlwindUpgradeCost) {
		this->Character->WhirlwindDamage += 0.1f;
		this->Character->TimeFragments -= this->GameMode->WhirlwindUpgradeCost;
		this->GameMode->WhirlwindUpgradeCost *= 2;
	}
}

void UShopMenuWidget::OnUpgradeHelicopterClick() {
	if (this->Character->TimeFragments >= this->GameMode->HelicopterUpgradeCost) {
		this->Character->HelicopterDamage += 0.15f;
		this->Character->TimeFragments -= this->GameMode->HelicopterUpgradeCost;
		this->GameMode->HelicopterUpgradeCost *= 2;
	}
}

void UShopMenuWidget::OnUpgradeLeapClick() {
	if (this->Character->TimeFragments >= this->GameMode->LeapUpgradeCost) {
		this->Character->LeapDamage += 0.2f;
		this->Character->TimeFragments -= this->GameMode->LeapUpgradeCost;
		this->GameMode->LeapUpgradeCost *= 2;
	}
}
