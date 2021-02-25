// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "TimeFragment.h"
#include "GameFramework/Character.h"
#include "DummyMaster.generated.h"

UCLASS(config=Game)
class ADummyMaster : public ACharacter {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Classes)
	TSubclassOf<ATimeFragment> DefaultCollectableClass;

protected:
	UParticleSystem* ExplosionParticle;

public:
	ADummyMaster();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};

