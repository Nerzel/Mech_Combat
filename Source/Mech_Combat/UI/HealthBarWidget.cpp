#include "HealthBarWidget.h"


#include "Kismet/GameplayStatics.h"
#include "Mech_Combat/Mech_CombatCharacter.h"

UHealthBarWidget::UHealthBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
}

void UHealthBarWidget::NativeConstruct() {
    Super::NativeConstruct();

    this->Character = Cast<AMech_CombatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

void UHealthBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
    Super::NativeTick(MyGeometry, InDeltaTime);

    if (this->HealthBar) {
        this->HealthBar->SetPercent(Character->Health);
    }
}
