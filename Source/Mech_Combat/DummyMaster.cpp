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

	static ConstructorHelpers::FClassFinder<ATimeFragment> TimeFragmentBPClass(TEXT("/Game/MechCombat/Blueprints/TimeFragment_BP"));
	if (TimeFragmentBPClass.Class != NULL) {
		DefaultCollectableClass = TimeFragmentBPClass.Class;
	}
	this->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADummyMaster::OnBeginOverlap);

	this->Health = 1.0f;
}

void ADummyMaster::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AMech_CombatCharacter* Character;

	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor && OtherActor->IsA<AHammerWeapon>()) {
		Character = Cast<AMech_CombatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

		if (Character->DamageType != 0) {

			switch (Character->DamageType) {
				case 1:
					this->Health -= Cast<AHammerWeapon>(OtherActor)->BaseDamage + 0.2f;
					if (Character->AttackEnergy < 12) {
						Character->AttackEnergy++;
					}
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
				FActorSpawnParameters SpawnParams;

				SpawnParams.Owner = this;
				SpawnParams.Instigator = this;
				GetWorld()->SpawnActor<ATimeFragment>(this->DefaultCollectableClass, GetActorTransform(), SpawnParams);

				Destroy();
			}
		}

	}

}
