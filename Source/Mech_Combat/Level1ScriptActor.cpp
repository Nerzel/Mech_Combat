// Copyright Nerzel. All Rights Reserved.


#include "Level1ScriptActor.h"

ALevel1ScriptActor::ALevel1ScriptActor() {

}

void ALevel1ScriptActor::BeginPlay() {
	Super::BeginPlay();

	this->GameMode = Cast<AMech_CombatGameMode>(GetWorld()->GetAuthGameMode());
	this->GameMode->WaveNumber = 1;
	UE_LOG(LogTemp, Warning, TEXT("okokokkook"));
}
