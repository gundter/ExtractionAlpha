// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ExtractionCharacterBase.generated.h"

UCLASS()
class EXTRACTIONALPHA_API AExtractionCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AExtractionCharacterBase();

protected:
	virtual void BeginPlay() override;
};
