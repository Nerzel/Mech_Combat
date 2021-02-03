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

public:
	ADummyMaster();
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};

