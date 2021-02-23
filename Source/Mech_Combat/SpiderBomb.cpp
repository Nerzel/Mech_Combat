// Copyright Nerzel. All Rights Reserved.


#include "SpiderBomb.h"

// Sets default values
ASpiderBomb::ASpiderBomb() {
    this->CarriedBombMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CarriedBombMesh"));
    this->CarriedBombMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("Core")));

    this->bIsArmed = false;
}
