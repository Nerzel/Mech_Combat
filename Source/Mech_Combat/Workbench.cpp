// Copyright Nerzel. All Rights Reserved.


#include "Workbench.h"


#include "Mech_CombatCharacter.h"
#include "Kismet/KismetMathLibrary.h"

AWorkbench::AWorkbench() {
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneComponent"));
	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	this->Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	this->BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));
	this->BoxComponent->AttachToComponent(this->Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	this->BoxComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	this->BoxComponent->SetNotifyRigidBodyCollision(true);
	this->TextRender1Component = CreateDefaultSubobject<UTextRenderComponent>(FName("TextRender1"));
	this->TextRender1Component->AttachToComponent(this->Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	this->TextRender1Component->SetHorizontalAlignment(EHTA_Center);
	this->TextRender1Component->SetVerticalAlignment(EVRTA_TextCenter);
	this->TextRender2Component = CreateDefaultSubobject<UTextRenderComponent>(FName("TextRender2"));
	this->TextRender2Component->AttachToComponent(this->Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	this->TextRender2Component->SetHorizontalAlignment(EHTA_Center);
	this->TextRender2Component->SetVerticalAlignment(EVRTA_TextCenter);

	PrimaryActorTick.bCanEverTick = true;
}

void AWorkbench::PostInitializeComponents() {
	Super::PostInitializeComponents();

	this->BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWorkbench::OnBeginOverlap);
	this->BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AWorkbench::OnEndOverlap);
}

void AWorkbench::Tick(float DeltaSeconds) {
	FRotator TextRenderRotation;

	Super::Tick(DeltaSeconds);

	TextRenderRotation = UKismetMathLibrary::FindLookAtRotation(this->TextRender1Component->GetComponentLocation(),
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation());
	this->TextRender1Component->SetWorldRotation(TextRenderRotation);
	this->TextRender2Component->SetWorldRotation(TextRenderRotation);
}

void AWorkbench::OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (OtherActor && OtherActor->IsA<AMech_CombatCharacter>()) {
		Cast<AMech_CombatCharacter>(OtherActor)->bIsAtBench = true;
	}

}

void AWorkbench::OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {

	if (OtherActor && OtherActor->IsA<AMech_CombatCharacter>()) {
		Cast<AMech_CombatCharacter>(OtherActor)->bIsAtBench = false;
	}

}

