// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ExtractionCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AExtractionCharacter::AExtractionCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.f, 0.f);
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(GetMesh(), "Camera");
	FollowCamera->bUsePawnControlRotation = true;
}

void AExtractionCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AExtractionCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
