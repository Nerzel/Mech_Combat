// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HammerWeapon.h"
#include "GameFramework/Character.h"
#include "UI/DefaultCharacterHUDWidget.h"
#include "UI/ShopMenuWidget.h"


#include "Mech_CombatCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FStopSprintingDelegate, bool);

UCLASS(config=Game)
class AMech_CombatCharacter : public ACharacter {

	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AMech_CombatCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Boolean to evaluate the attack state */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	bool bIsAttacking;

	/** Boolean to evaluate the sprinting state */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	bool bIsSprinting;

	/** Boolean to evaluate when an attack animation is already running */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	bool bIsAlreadyAttacking;
	/** Boolean to say when the whirlwind attack is running */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	bool bIsWirlwindActive;

	/** Boolean to say when the helicopter attack is running */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	bool bIsHelicopterActive;

	/** Boolean to say when the leap is running */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	bool bIsLeapctive;
	/** This integer determines the type of damage (useful to calculate the amount of damage done per attack) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	int DamageType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	float MaxStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	int DefaultMovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	int MovementSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	float Stamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	float NormalDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	int AttackEnergy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	int TimeFragments;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	bool bIsAtBench;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character)
	bool bIsShopOpened;

	UPROPERTY(EditDefaultsOnly, Category=HUD)
	TSubclassOf<UDefaultCharacterHUDWidget> DefaultCharacterHUDClass;

	UPROPERTY(EditDefaultsOnly, Category=HUD)
	TSubclassOf<UShopMenuWidget> DefaultShopMenuClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Weapon)
	TSubclassOf<AHammerWeapon> HammerWeaponBP;

private:
	bool PlayAttackAnimation;
	FTimerHandle AttackAnimationTimer;
	FTimerHandle EnergyDecreaseTimer;
	FTimerHandle EnergyIncreaseTimer;
	FTimerHandle LeapTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UDefaultCharacterHUDWidget* CharacterHUDWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UShopMenuWidget* ShopMenuWidget;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/** Called when attack button is triggered down */
	void Attack();

	/** Called when attack button is released */
	void StopAttack();

	/** Called when attack button is done to stop the animation */
	void ResetAttack();

	/** Called when srpint button is triggered down */
	void StartSprinting();

	/** Called when srpint button is released to get back to normal speed*/
	void StopSprinting(const bool bRefillStamina);

	/** Called by timer handler to decrease energy while sprinting*/
	void DecreaseStaminaWhileSprinting();

	/** Called by timer handler to increase energy after sprinting*/
	void IncreaseStaminaAfterSprinting();

	void ExecuteWhirlwindAttack();

	void StopWhirlwindAttack();

	void ExecuteHelicopterAttack();

	void StopHelicopterAttack();

	void ExecuteLeap();

	void StopLeap();


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	virtual void BeginPlay() override;
	UDefaultCharacterHUDWidget* GetCharacterHUDWidget();
	UShopMenuWidget* GetShopMenHUDWidget();
	void ToggleShopMenu();
	void AutoIncreaseStamina();

};

