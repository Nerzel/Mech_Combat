// Copyright Nerzel. All Rights Reserved.


#include "SpiderBomb.h"

#include "Mech_CombatCharacter.h"

// Sets default values
ASpiderBomb::ASpiderBomb() {
    this->CarriedBombMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CarriedBombMesh"));
    this->CarriedBombMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("Core")));
    this->PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
    this->PawnSensing->SetPeripheralVisionAngle(60.0f);
    this->PawnSensing->SightRadius = 6000.0F;

    this->bIsArmed = false;
}

void ASpiderBomb::PostInitializeComponents() {
    Super::PostInitializeComponents();

    this->PawnSensing->OnSeePawn.AddDynamic(this, &ASpiderBomb::OnSeePawn);
}

void ASpiderBomb::OnSeePawn(APawn *OtherPAwn) {
    if (OtherPAwn && OtherPAwn->IsA<AMech_CombatCharacter>()) {
        UE_LOG(LogTemp, Warning, TEXT("ok"));
    }
}