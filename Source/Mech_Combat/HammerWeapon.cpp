// Fill out your copyright notice in the Description page of Project Settings.


#include "HammerWeapon.h"

// Sets default values
AHammerWeapon::AHammerWeapon() {
	this->Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	this->Mesh->SetGenerateOverlapEvents(true);
	RootComponent = this->Mesh;

	PrimaryActorTick.bCanEverTick = true;

	this->BaseDamage = 0.1f;
}

// Called when the game starts or when spawned
void AHammerWeapon::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AHammerWeapon::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
