// Copyright Nerzel. All Rights Reserved.


#include "SpiderBomb.h"

#include "DefaultAIController.h"
#include "Mech_CombatCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpiderBomb::ASpiderBomb() {
    this->CarriedBombMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CarriedBombMesh"));
    this->CarriedBombMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("Core")));
    this->PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
    this->PawnSensing->SetPeripheralVisionAngle(60.f);
    this->PawnSensing->SightRadius = 6000.f;
    this->BombRadius = CreateDefaultSubobject<USphereComponent>(TEXT("BombRadius"));
    this->BombRadius->SetupAttachment(RootComponent);
    this->BombRadius->InitSphereRadius(400.f);
    AIControllerClass = ADefaultAIController::StaticClass();

    this->bIsArmed = false;
    this->bIsPlayerInRadius = false;
}

void ASpiderBomb::BeginPlay() {
    Super::BeginPlay();

    this->Character = Cast<AMech_CombatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}


void ASpiderBomb::PostInitializeComponents() {
    Super::PostInitializeComponents();

    if (this->PawnSensing) {
        this->PawnSensing->OnSeePawn.AddDynamic(this, &ASpiderBomb::OnSeePawn);
    }
}

void ASpiderBomb::OnSeePawn(APawn *OtherPAwn) {
   AAIController* AIController;

    if (OtherPAwn && OtherPAwn->IsA<AMech_CombatCharacter>()) {
        AIController = Cast<ADefaultAIController>(GetController());
        if (AIController && this->Character) {
            AIController->MoveToActor( this->Character, 200.f);
        }
    }
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
        this->Character->Health -= 0.3f;
    }
    Destroy();
}

void ASpiderBomb::NotifyActorBeginOverlap(AActor* OtherActor) {
    if (OtherActor->IsA<AMech_CombatCharacter>()) {
        this->bIsPlayerInRadius = true;
    }
}

void ASpiderBomb::NotifyActorEndOverlap(AActor* OtherActor) {
    if (OtherActor->IsA<AMech_CombatCharacter>()) {
        this->bIsPlayerInRadius = false;
    }
}