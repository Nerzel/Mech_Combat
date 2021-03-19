// Copyright Nerzel. All Rights Reserved.


#include "Level1ScriptActor.h"

ALevel1ScriptActor::ALevel1ScriptActor() {
	this->EnnemyTypeFlag = true;
}

void ALevel1ScriptActor::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

void ALevel1ScriptActor::BeginPlay() {
	Super::BeginPlay();

	this->GameMode = Cast<AMech_CombatGameMode>(GetWorld()->GetAuthGameMode());

	if (this->DoorsTriggerBox) {
		this->DoorsTriggerBox->OnActorBeginOverlap.AddDynamic(this, &ALevel1ScriptActor::OnDoorsTriggerBoxBeginOverlap);
		this->DoorsTriggerBox->OnActorEndOverlap.AddDynamic(this, &ALevel1ScriptActor::OnDoorsTriggerBoxEndOverlap);
	}

	if (this->DoorsLevelSequence) {
		ALevelSequenceActor* SequenceActor;
		this->DoorsSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), this->DoorsLevelSequence, FMovieSceneSequencePlaybackSettings(), SequenceActor);
	}

	SpawnBots();
}

void ALevel1ScriptActor::SpawnBots() {

	if (this->Spawners.Num()) {
		GetWorld()->GetTimerManager().SetTimer(this->SpawnTimer, this, &ALevel1ScriptActor::SpawnBotByClass, 3.f, false);
	}

}

void ALevel1ScriptActor::SpawnBotByClass() {

	if (this->EnnemyTypeFlag) {
		Spawners[FMath::RandRange(0, Spawners.Num() - 1)]->SpawnBot(DefaultSpiderBombClass);
	} else {
		Spawners[FMath::RandRange(0, Spawners.Num() - 1)]->SpawnBot(DefaultSpiderTurretClass);
	}

	if (this->GameMode->NumberOfBots + this->GameMode->NumberOfKills == this->GameMode->MaxBots) {
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	}

	if (!this->NewWaveCheckTimer.IsValid()) {
		GetWorld()->GetTimerManager().SetTimer(this->NewWaveCheckTimer, this, &ALevel1ScriptActor::CheckNewWave, 2.f, true);
	}

	this->EnnemyTypeFlag = !this->EnnemyTypeFlag;
}

void ALevel1ScriptActor::CheckNewWave() {

	if (this->GameMode->NumberOfKills == this->GameMode->MaxBots) {
		GetWorld()->GetTimerManager().ClearTimer(this->NewWaveCheckTimer);
		this->GameMode->NumberOfKills = 0;
		this->GameMode->TriggerNextWave();
		SpawnBots();
	}

}

void ALevel1ScriptActor::OnDoorsTriggerBoxBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) {
	if (OtherActor->IsA<AMech_CombatCharacter>() && this->DoorsSequencePlayer) {
		this->DoorsSequencePlayer->Play();
	}
}

void ALevel1ScriptActor::OnDoorsTriggerBoxEndOverlap(AActor* OverlappedActor, AActor* OtherActor) {
	if (OtherActor->IsA<AMech_CombatCharacter>() && this->DoorsSequencePlayer) {
		this->DoorsSequencePlayer->PlayReverse();
	}
}
