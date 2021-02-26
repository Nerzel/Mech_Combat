// Copyright Nerzel. All Rights Reserved.


#include "SpiderBomb.h"

#include "DefaultAIController.h"
#include "Mech_CombatCharacter.h"
#include "NavigationSystem.h"
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
    this->BombRadius->InitSphereRadius(500.f);
    this->BombRadius->OnComponentBeginOverlap.AddDynamic(this, &ASpiderBomb::OnBombRadiusBeginOverlap);
    AIControllerClass = ADefaultAIController::StaticClass();

    this->bIsArmed = false;
    this->bIsPlayerInRadius = false;
    this->bIsChasing = false;
    this->RoamingRadius = 5000.f;
}

void ASpiderBomb::BeginPlay() {
    Super::BeginPlay();

    this->Character = Cast<AMech_CombatCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
    this->AIController = Cast<ADefaultAIController>(GetController());
    RoamToRandomLocation();
}

void ASpiderBomb::PostInitializeComponents() {
    Super::PostInitializeComponents();

    if (this->PawnSensing) {
        this->PawnSensing->OnSeePawn.AddDynamic(this, &ASpiderBomb::OnSeePawn);
    }
}

void ASpiderBomb::OnSeePawn(APawn *OtherPAwn) {
    if (OtherPAwn && OtherPAwn->IsA<AMech_CombatCharacter>()) {
        if (AIController && this->Character) {
            this->bIsChasing = true;
            this->AIController->MoveToActor( this->Character, 200.f);
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

void ASpiderBomb::RoamToRandomLocation() {
     const UNavigationSystemV1* navSystem = UNavigationSystemV1::GetCurrent(this);
     FNavLocation NavLoc;

     if (navSystem->GetRandomReachablePointInRadius(GetActorLocation(), this->RoamingRadius, NavLoc)) {
         this->AIController->MoveToLocation(NavLoc);
     }
}

void ASpiderBomb::OnBombRadiusBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    if (OtherActor->IsA<AMech_CombatCharacter>()) {
        this->bIsPlayerInRadius = true;
    }
}

void ASpiderBomb::OnBombRadiusEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
    if (OtherActor->IsA<AMech_CombatCharacter>()) {
         this->bIsPlayerInRadius = false;
     }
}
