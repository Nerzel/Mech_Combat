// Copyright Nerzel. All Rights Reserved.


#include "SpiderTurret.h"

// Sets default values
ASpiderTurret::ASpiderTurret() {
	this->CarriedTurretMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CarriedTurretbMesh"));
	this->CarriedTurretMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("Core")));

	this->bIsShooting = false;
}