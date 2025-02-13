// Copyright Nerzel. All Rights Reserved.


#include "SpiderBomb.h"

#include "Mech_CombatCharacter.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpiderBomb::ASpiderBomb() {
    this->CarriedBombMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CarriedBombMesh"));
    this->CarriedBombMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("Core")));
    this->BombRadius = CreateDefaultSubobject<USphereComponent>(TEXT("BombRadius"));
    this->BombRadius->SetupAttachment(RootComponent);
    this->BombRadius->InitSphereRadius(500.f);

    this->bIsArmed = false;
    this->bIsPlayerInRadius = false;
}

void ASpiderBomb::PostInitializeComponents() {
    Super::PostInitializeComponents();

    if (this->BombRadius) {
        this->BombRadius->OnComponentBeginOverlap.AddDynamic(this, &ASpiderBomb::OnBombRadiusBeginOverlap);
        this->BombRadius->OnComponentEndOverlap.AddDynamic(this, &ASpiderBomb::OnBombRadiusEndOverlap);
    }
}

void ASpiderBomb::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    Super::EndPlay(EndPlayReason);

    GetWorldTimerManager().ClearTimer(this->ExplodeTimer);
}


void ASpiderBomb::ArmAndDestroy() {
    this->bIsArmed = true;
    if (!ExplodeTimer.IsValid()) {
        GetWorldTimerManager().SetTimer(ExplodeTimer, this, &ASpiderBomb::ExplodeAndDestroy, 3.f, false);
    }
}

void ASpiderBomb::ExplodeAndDestroy() {
    if (ExplosionParticle) {
        UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionParticle, GetActorLocation(), FRotator::ZeroRotator, FVector(5.f));
    }
    if (this->bIsPlayerInRadius) {
        PlayerCharacter->Health -= 0.3f;
        PlayerCharacter->UpdateHealthBar();

        if (PlayerCharacter->Health <= 0.f) {
            PlayerCharacter->Death();
        }
    }

    Cast<AMech_CombatGameMode>(GetWorld()->GetAuthGameMode())->ModifyNumberOfBots(-1);
    Cast<AMech_CombatGameMode>(GetWorld()->GetAuthGameMode())->NumberOfKills++;
    Destroy();
}

void ASpiderBomb::OnBombRadiusBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    if (OtherActor->IsA<AMech_CombatCharacter>()) {
        this->bIsPlayerInRadius = true;
    }
}

void ASpiderBomb::OnBombRadiusEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
    if (OtherActor->IsA<AMech_CombatCharacter>()) {
         this->bIsPlayerInRadius = false;
     }
}
