// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HammerWeapon.generated.h"

UCLASS()
class MECH_COMBAT_API AHammerWeapon : public AActor {

	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float BaseDamage;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AHammerWeapon();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE class USkeletalMeshComponent* GetMesh() const { return Mesh; }

};
