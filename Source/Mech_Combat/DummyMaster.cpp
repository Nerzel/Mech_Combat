// Copyright Nerzel. All Rights Reserved.

#include "DummyMaster.h"

#include "DefaultAIController.h"
#include "HammerWeapon.h"
#include "Mech_CombatCharacter.h"
#include "NavigationSystem.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Perception/PawnSensingComponent.h"

//////////////////////////////////////////////////////////////////////////
// ADummyMaster

ADummyMaster::ADummyMaster() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(120.f, 140.0f);
	this->PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	this->PawnSensing->SetPeripheralVisionAngle(60.f);
	this->PawnSensing->SightRadius = 6000.f;

	AIControllerClass = ADefaultAIController::StaticClass();

	this->Health = 1.0f;
	this->bIsChasing = false;
	this->RoamingRadius = 5000.f;
	this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	this->bIsPlayerLocked = false;
	PrimaryActorTick.bCanEverTick = true;
}

void ADummyMaster::PostInitializeComponents() {
	Super::PostInitializeComponents();

	if (this->PawnSensing) {
		this->PawnSensing->OnSeePawn.AddDynamic(this, &ADummyMaster::OnSeePawn);
	}

	if (this->GetCapsuleComponent()) {
		this->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADummyMaster::OnBeginOverlap);
	}
}

void ADummyMaster::BeginPlay() {
	Super::BeginPlay();

	this->PlayerCharacter = Cast<AMech_CombatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	this->AIController = Cast<ADefaultAIController>(GetController());
	RoamToRandomLocation();
}

void ADummyMaster::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	if (this->bIsPlayerLocked) {
		this->AIController->MoveToActor( this->PlayerCharacter, 200.f, true, true, true);
	}
}

void ADummyMaster::OnSeePawn(APawn *OtherPAwn) {
	if (OtherPAwn && OtherPAwn->IsA<AMech_CombatCharacter>()) {
		if (this->AIController && this->PlayerCharacter && !this->bIsChasing) {
			this->bIsChasing = true;
			this->AIController->MoveToActor( this->PlayerCharacter, 200.f, true, true, true);
		}
	}
}

void ADummyMaster::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	AMech_CombatCharacter* Character;

	if (OtherActor && OtherActor->IsA<AHammerWeapon>()) {
		Character = Cast<AMech_CombatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

		if (Character->DamageType != 0) {

			switch (Character->DamageType) {
				case 1:
					this->Health -= Cast<AHammerWeapon>(OtherActor)->BaseDamage + this->PlayerCharacter->NormalDamage;
					if (Character->AttackEnergy < 12) {
						Character->AttackEnergy++;
					}
					break;
				case 2:
					this->Health -= Cast<AHammerWeapon>(OtherActor)->BaseDamage + this->PlayerCharacter->WhirlwindDamage;
					break;
				case 3:
					this->Health -= Cast<AHammerWeapon>(OtherActor)->BaseDamage + this->PlayerCharacter->HelicopterDamage;
					break;
				case 4:
					this->Health -= Cast<AHammerWeapon>(OtherActor)->BaseDamage + this->PlayerCharacter->LeapDamage;
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

				Cast<AMech_CombatGameMode>(GetWorld()->GetAuthGameMode())->NumberOfBots--;
				Cast<AMech_CombatGameMode>(GetWorld()->GetAuthGameMode())->NumberOfKills++;
				Destroy();
			}
		}

	}

}

void ADummyMaster::RoamToRandomLocation() {
	if (!this->bIsChasing) {
		const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(this);
		FNavLocation NavLoc;

		if (NavSystem->GetRandomReachablePointInRadius(GetActorLocation(), this->RoamingRadius, NavLoc)) {
			this->AIController->MoveToLocation(NavLoc);
		}
	}
}
