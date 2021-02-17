// Copyright Nerzel. All Rights Reserved.

#include "DummyMaster.h"


#include "HammerWeapon.h"
#include "Mech_CombatCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

//////////////////////////////////////////////////////////////////////////
// ADummyMaster

ADummyMaster::ADummyMaster() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ExplosionParticleAsset(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (ExplosionParticleAsset.Object != NULL) {
		this->ExplosionParticle = ExplosionParticleAsset.Object;
	}
	this->Health = 1.0f;
}

void ADummyMaster::NotifyActorEndOverlap(AActor* OtherActor) {
	AMech_CombatCharacter* Character;

	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor && OtherActor->IsA<AHammerWeapon>()) {
		Character = Cast<AMech_CombatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

		if (Character->DamageType != 0) {

			switch (Character->DamageType) {
				case 1:
					this->Health -= Cast<AHammerWeapon>(OtherActor)->BaseDamage + 0.2f;
					break;
				case 2:
					this->Health -= Cast<AHammerWeapon>(OtherActor)->BaseDamage + 0.1f;
					break;
				case 3:
					this->Health -= Cast<AHammerWeapon>(OtherActor)->BaseDamage + 0.2f;
					break;
				case 4:
					this->Health -= Cast<AHammerWeapon>(OtherActor)->BaseDamage + 0.4f;
					break;
				default:
					break;
			}

			if (this->ExplosionParticle) {
				UGameplayStatics::SpawnEmitterAtLocation(this, this->ExplosionParticle, GetActorLocation());
			}

			if (this->Health <= 0) {
				Destroy();
			}
		}

	}

}
