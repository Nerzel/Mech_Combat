// Copyright Nerzel. All Rights Reserved.


#include "ShopMenuWidget.h"

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
	if (this->ReplenishHealthPrice) {
		this->ReplenishHealthPrice->SetText(FText::AsNumber(this->GameMode->ReplenishHealthPrice, &this->FormatingOptions2Ints));
	}
	if (this->ReplenishStaminaPrice) {
		this->ReplenishStaminaPrice->SetText(FText::AsNumber(this->GameMode->ReplenishStaminahPrice, &this->FormatingOptions2Ints));
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
}

void UShopMenuWidget::OnReplishHealthClick() {
	if (this->Character->TimeFragments >= this->GameMode->ReplenishHealthPrice && this->Character->Health < 1.f) {
		this->Character->Health = 1.0;
		this->Character->TimeFragments -= this->GameMode->ReplenishHealthPrice;
	}
}

void UShopMenuWidget::OnReplishStaminaClick() {
	if (this->Character->TimeFragments >= this->GameMode->ReplenishStaminahPrice && this->Character->Stamina < 1.f) {
		this->Character->Stamina = 1.0;
		this->Character->TimeFragments -= this->GameMode->ReplenishStaminahPrice;
	}
}
