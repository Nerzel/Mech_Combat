// Copyright Nerzel. All Rights Reserved.

#include "DummyMaster.h"


#include "HammerWeapon.h"
#include "Mech_CombatCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// ADummyMaster

ADummyMaster::ADummyMaster() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	this->Health = 1.0f;
}

void ADummyMaster::NotifyActorEndOverlap(AActor* OtherActor) {
	AMech_CombatCharacter* Character;

	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor && OtherActor->IsA<AHammerWeapon>()) {
		Character = Cast<AMech_CombatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
		if (Character->IsAttacking) {
			this->Health -= Cast<AHammerWeapon>(OtherActor)->BaseDamage;
			if (this->Health <= 0) {
				Destroy();
			}
		}
	}
}
