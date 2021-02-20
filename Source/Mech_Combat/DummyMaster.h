// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DummyMaster.generated.h"

UCLASS(config=Game)
class ADummyMaster : public ACharacter {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Health;

private:
	UParticleSystem* ExplosionParticle;

public:
	ADummyMaster();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};

