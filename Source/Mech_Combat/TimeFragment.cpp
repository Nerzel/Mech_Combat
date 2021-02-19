// Copyright Nerzel. All Rights Reserved.


#include "TimeFragment.h"

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
	Super::BeginPlay();
}

// Called every frame
void ATimeFragment::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

