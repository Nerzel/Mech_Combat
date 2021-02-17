// Fill out your copyright notice in the Description page of Project Settings.


#include "HammerWeapon.h"

// Sets default values
AHammerWeapon::AHammerWeapon() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	this->Mesh->AttachToComponent(this->RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	this->Mesh->SetGenerateOverlapEvents(true);
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

