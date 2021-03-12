// Copyright Nerzel. All Rights Reserved.


#include "SpiderTurret.h"

#include "Projectile.h"

// Sets default values
ASpiderTurret::ASpiderTurret() {
	this->CarriedTurretMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CarriedTurretbMesh"));
	this->CarriedTurretMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("Core")));
	this->bIsShooting = false;
	this->ShootRate = 0.4f;
	this->ShootRange = 1500.f;
}

void ASpiderTurret::BeginPlay() {
	Super::BeginPlay();
}

void ASpiderTurret::Shoot() {
	GetWorld()->SpawnActor<AProjectile>(this->DefaultProjectileClass, this->CarriedTurretMesh->GetSocketTransform(FName("RightEdge")));
	GetWorld()->SpawnActor<AProjectile>(this->DefaultProjectileClass, this->CarriedTurretMesh->GetSocketTransform(FName("LeftEdge")));
}

void ASpiderTurret::OnSeePawn(APawn *OtherPAwn) {
	Super::OnSeePawn(OtherPAwn);

	if (OtherPAwn && OtherPAwn->IsA<AMech_CombatCharacter>()) {
		if (GetDistanceTo(OtherPAwn) < this->ShootRange) {
			this->bIsShooting = true;
			GetWorldTimerManager().SetTimer(ShootingTimer, this, &ASpiderTurret::Shoot, this->ShootRate, true);
		} else {
			this->bIsShooting = false;
			GetWorldTimerManager().ClearTimer(ShootingTimer);
		}
	}
}
