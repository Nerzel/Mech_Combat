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
	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

