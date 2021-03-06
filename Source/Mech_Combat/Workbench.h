// Copyright Nerzel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"


#include "Workbench.generated.h"

/**
 * 
 */
UCLASS()
class MECH_COMBAT_API AWorkbench : public AActor {

	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTextRenderComponent* TextRender1Component;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTextRenderComponent* TextRender2Component;

public:
	AWorkbench();
	virtual void Tick(float DeltaSeconds) override;
	virtual void PostInitializeComponents() override;
	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
