// Copyright Epic Games, Inc. All Rights Reserved.

#include "Mech_CombatCharacter.h"

#include "HammerWeapon.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// AMech_CombatCharacter

AMech_CombatCharacter::AMech_CombatCharacter() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	this->bIsAttacking = false;
	this->bIsAlreadyAttacking = false;
	this->bIsSprinting = false;
	this->bIsWirlwindActive = false;
	this->bIsHelicopterActive = false;
	this->bIsLeapctive = false;
	this->PlayAttackAnimation = false;
	this->MaxHealth = 1.f;
	this->Health = this->MaxHealth;
	this->MaxStamina = 1.f;
	this->Stamina = this->MaxStamina;
	this->DefaultMovementSpeed = 600;
	this->MovementSpeed= this->DefaultMovementSpeed;
	this->AttackEnergy = 12;
	this->DamageType = 0;
	this->TimeFragments = 50;
	this->bIsAtBench = false;
	this->bIsShopOpened = false;
	this->NormalDamage = 0.2f;
	this->WhirlwindDamage = 0.1f;
	this->HelicopterDamage = 0.2f;
	this->LeapDamage = 0.4f;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMech_CombatCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("DefaultAttack", IE_Pressed, this, &AMech_CombatCharacter::Attack);
	PlayerInputComponent->BindAction("DefaultAttack", IE_Released, this, &AMech_CombatCharacter::StopAttack);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMech_CombatCharacter::StartSprinting);
	PlayerInputComponent->BindAction<FStopSprintingDelegate>("Sprint", IE_Released, this, &AMech_CombatCharacter::StopSprinting, true);
	PlayerInputComponent->BindAction("WhirlwindAttack", IE_Pressed, this, &AMech_CombatCharacter::ExecuteWhirlwindAttack);
	PlayerInputComponent->BindAction("WhirlwindAttack", IE_Released, this, &AMech_CombatCharacter::StopWhirlwindAttack);
	PlayerInputComponent->BindAction("HelicopterAttack", IE_Pressed, this, &AMech_CombatCharacter::ExecuteHelicopterAttack);
	PlayerInputComponent->BindAction("HelicopterAttack", IE_Released, this, &AMech_CombatCharacter::StopHelicopterAttack);
	PlayerInputComponent->BindAction("Leap", IE_Pressed, this, &AMech_CombatCharacter::ExecuteLeap);
	PlayerInputComponent->BindAction("ShopMenu", IE_Pressed, this, &AMech_CombatCharacter::ToggleShopMenu);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMech_CombatCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMech_CombatCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMech_CombatCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMech_CombatCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMech_CombatCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMech_CombatCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMech_CombatCharacter::OnResetVR);
}


void AMech_CombatCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMech_CombatCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AMech_CombatCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AMech_CombatCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMech_CombatCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMech_CombatCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMech_CombatCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMech_CombatCharacter::Attack() {
	bIsAttacking = true;
	bIsAlreadyAttacking = true;
	PlayAttackAnimation = true;
	this->DamageType = 1;
	GetWorldTimerManager().SetTimer(AttackAnimationTimer, this, &AMech_CombatCharacter::ResetAttack, 0.56f, true);
}

void AMech_CombatCharacter::StopAttack() {
	PlayAttackAnimation = false;
}

void AMech_CombatCharacter::ResetAttack() {
	if (!PlayAttackAnimation) {
		bIsAttacking = false;
		bIsAlreadyAttacking = false;
		this->DamageType = 0;
		GetWorldTimerManager().ClearTimer(AttackAnimationTimer);
	}
}

void AMech_CombatCharacter::BeginPlay() {
	FTransform HammerSocketTransform;
	USkeletalMeshComponent* CharacterMesh;

	Super::BeginPlay();

	if (this->DefaultCharacterHUDClass) {
		this->CharacterHUDWidget = CreateWidget<UDefaultCharacterHUDWidget>(GetWorld(), DefaultCharacterHUDClass, FName(TEXT("DefaultCharacterHUD")));
		this->CharacterHUDWidget->AddToViewport();
	}

	if (this->DefaultShopMenuClass) {
		this->ShopMenuWidget = CreateWidget<UShopMenuWidget>(GetWorld(), DefaultShopMenuClass, FName(TEXT("DefaultShopMenu")));
		this->ShopMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		this->ShopMenuWidget->AddToViewport();
	}

	CharacterMesh = GetMesh();
	HammerSocketTransform = CharacterMesh->GetSocketTransform(FName(TEXT("HammerSocket")), RTS_World);
	this->HammerWeapon = GetWorld()->SpawnActor<AHammerWeapon>(this->DefaultHammerWeaponClass, HammerSocketTransform);
	this->HammerWeapon->AttachToComponent(
		CharacterMesh,
		FAttachmentTransformRules(
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			true
		),
		FName(TEXT("HammerSocket"))
	);
}

UDefaultCharacterHUDWidget* AMech_CombatCharacter::GetCharacterHUDWidget() {
	return this->CharacterHUDWidget;
}

UShopMenuWidget* AMech_CombatCharacter::GetShopMenHUDWidget() {
	return this->ShopMenuWidget;
}

void AMech_CombatCharacter::StartSprinting() {
	if (this->Stamina > 0.0f) {
		this->bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = this->MovementSpeed * 2;
		GetWorldTimerManager().SetTimer(EnergyDecreaseTimer, this, &AMech_CombatCharacter::DecreaseStaminaWhileSprinting, 1.0f, true);
	}
	if (EnergyIncreaseTimer.IsValid()) {
		GetWorldTimerManager().ClearTimer(EnergyIncreaseTimer);
	}
}

void AMech_CombatCharacter::StopSprinting(const bool bRefillStamina) {
	if (this->bIsSprinting) {
		this->bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed =  this->MovementSpeed;
		GetWorldTimerManager().ClearTimer(EnergyDecreaseTimer);
	}
	if (this->Stamina < this->MaxStamina && bRefillStamina) {
		GetWorldTimerManager().SetTimer(EnergyIncreaseTimer, this, &AMech_CombatCharacter::IncreaseStaminaAfterSprinting, 1.0f, true);
	}
}

void AMech_CombatCharacter::DecreaseStaminaWhileSprinting() {
	this->Stamina -= 0.1f;
	if (this->Stamina <= 0.0f) {
		StopSprinting(false);
	}
}

void AMech_CombatCharacter::IncreaseStaminaAfterSprinting() {
	if (this->Stamina < this->MaxStamina) {
		this->Stamina += 0.05f;
	} else {
		GetWorldTimerManager().ClearTimer(EnergyIncreaseTimer);
	}
}

void AMech_CombatCharacter::AutoIncreaseStamina() {
	if (!this->EnergyIncreaseTimer.IsValid()) {
		GetWorldTimerManager().SetTimer(EnergyIncreaseTimer, this, &AMech_CombatCharacter::IncreaseStaminaAfterSprinting, 1.0f, true);
	}
}

void AMech_CombatCharacter::ExecuteWhirlwindAttack() {
	if (!this->bIsAlreadyAttacking && this->AttackEnergy >= 3) {
		this->bIsWirlwindActive = true;
		this->bIsAlreadyAttacking = true;
		this->DamageType = 2;
		this->AttackEnergy -= 3;
	}
}

void AMech_CombatCharacter::StopWhirlwindAttack() {
	if (this->bIsWirlwindActive) {
		this->bIsWirlwindActive = false;
		this->bIsAlreadyAttacking = false;
		this->DamageType = 0;
	}
}

void AMech_CombatCharacter::ExecuteHelicopterAttack() {
	if (!this->bIsAlreadyAttacking && this->AttackEnergy >= 2) {
		this->bIsHelicopterActive = true;
		this->bIsAlreadyAttacking = true;
		this->DamageType = 3;
		this->AttackEnergy -= 2;
	}
}

void AMech_CombatCharacter::StopHelicopterAttack() {
	if (this->bIsHelicopterActive) {
		this->bIsHelicopterActive = false;
		this->bIsAlreadyAttacking = false;
		this->DamageType = 0;
	}
}

void AMech_CombatCharacter::ExecuteLeap() {
	if (!this->bIsAlreadyAttacking && this->AttackEnergy >= 2) {
		this->bIsLeapctive = true;
		this->bIsAlreadyAttacking = true;
		this->DamageType = 4;
		this->AttackEnergy -= 2;

		GetCharacterMovement()->AddImpulse(GetActorForwardVector() * 1000.0f + FVector(0.0f, 0.0f,600.0f), true);
		GetWorldTimerManager().SetTimer(LeapTimer, this, &AMech_CombatCharacter::StopLeap, 1.0f, false);
	}
}

void AMech_CombatCharacter::StopLeap() {
	GetWorldTimerManager().ClearTimer(LeapTimer);
	this->bIsLeapctive = false;
	this->bIsAlreadyAttacking = false;
	this->DamageType = 0;
}

void AMech_CombatCharacter::ToggleShopMenu() {

	if (this->bIsAtBench) {
		if (this->bIsShopOpened) {
			this->ShopMenuWidget->SetVisibility(ESlateVisibility::Hidden);
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
			this->bIsShopOpened = false;
		} else {
			this->ShopMenuWidget->SetVisibility(ESlateVisibility::Visible);
			GetCharacterMovement()->DisableMovement();
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameAndUI());
			this->bIsShopOpened = true;
		}
	}

}

void AMech_CombatCharacter::Death() {
	UGameplayStatics::SpawnEmitterAtLocation(this, this->ExplosionParticle, GetActorLocation(), FRotator::ZeroRotator, FVector(3.f));
	GetMesh()->SetVisibility(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->HammerWeapon->GetMesh()->SetVisibility(false);
	GetCharacterMovement()->DisableMovement();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	GetWorldTimerManager().SetTimer(this->DeathTimer, this, &AMech_CombatCharacter::GameOver, 1.f, false);
}

void AMech_CombatCharacter::GameOver() {
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}