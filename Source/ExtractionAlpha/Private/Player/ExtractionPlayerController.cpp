// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ExtractionPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

AExtractionPlayerController::AExtractionPlayerController()
{
	bReplicates = true;
}

void AExtractionPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AExtractionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(DefaultContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(DefaultContext, 0);
}

void AExtractionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AExtractionPlayerController::Move);
	
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AExtractionPlayerController::Look);

	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AExtractionPlayerController::ToggleAim);
	EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AExtractionPlayerController::ToggleAim);
	
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AExtractionPlayerController::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AExtractionPlayerController::StopJumping);
}

void AExtractionPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AExtractionPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AExtractionPlayerController::Jump()
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (ACharacter* ControlledCharacter = Cast<ACharacter>(ControlledPawn))
		{
			ControlledCharacter->Jump();
		}
	}
}

void AExtractionPlayerController::StopJumping()
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (ACharacter* ControlledCharacter = Cast<ACharacter>(ControlledPawn))
		{
			ControlledCharacter->StopJumping();
		}
	}
}

void AExtractionPlayerController::ToggleAim()
{
	bIsAiming = bIsAiming ? false : true;
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		if (const ACharacter* ControlledCharacter = Cast<ACharacter>(ControlledPawn))
		{
			ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = bIsAiming ? AimWalkSpeed : BaseWalkSpeed;
		}
	}
}
