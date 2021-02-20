// Copyright Nerzel. All Rights Reserved.


#include "TimeFragment.h"

#include "Mech_CombatCharacter.h"

// Sets default values
ATimeFragment::ATimeFragment() {
	RootComponent = CreateDefaultSubobject<USceneComponent>("DefaultSceneComponent");
	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	this->Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	this->Mesh->SetGenerateOverlapEvents(true);
	this->Mesh->SetCollisionProfileName(TEXT("OverlapAll"));
	this->RotatingMovementComponent = CreateOptionalDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovement"));
}

// Called when the game starts or when spawned
void ATimeFragment::BeginPlay() {
	FTimerDelegate Delegate;

	Super::BeginPlay();

	Delegate.BindLambda([this] { Destroy(); });

	GetWorldTimerManager().SetTimer(this->AutoDestroyTimer, Delegate, 30.0f, false);
}

// Called every frame
void ATimeFragment::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ATimeFragment::NotifyActorBeginOverlap(AActor* OtherActor) {
	Super::NotifyActorEndOverlap(OtherActor);

	if (OtherActor && OtherActor->IsA<AMech_CombatCharacter>()) {
		Cast<AMech_CombatCharacter>(OtherActor)->TimeFragments++;
		UE_LOG(LogTemp, Warning, TEXT("%d"), Cast<AMech_CombatCharacter>(OtherActor)->TimeFragments);
		Destroy();
	}
}
