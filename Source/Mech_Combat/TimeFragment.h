// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"

#include "TimeFragment.generated.h"

UCLASS()
class MECH_COMBAT_API ATimeFragment : public AActor {

	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	URotatingMovementComponent* RotatingMovementComponent;
	FTimerHandle AutoDestroyTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ATimeFragment();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor);
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

};
