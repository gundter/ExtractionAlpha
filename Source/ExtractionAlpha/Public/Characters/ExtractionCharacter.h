// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ExtractionCharacterBase.h"
#include "ExtractionCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class EXTRACTIONALPHA_API AExtractionCharacter : public AExtractionCharacterBase
{
	GENERATED_BODY()

public:
	AExtractionCharacter();
	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void BeginPlay() override;
private:

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* FollowCamera;

public:
	UCameraComponent* GetFollowCamera() const {return FollowCamera;}
};
