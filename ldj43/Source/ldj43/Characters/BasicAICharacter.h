// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GlobalCharacter.h"

#include "BasicAICharacter.generated.h"

UCLASS()
class LDJ43_API ABasicAICharacter : public AGlobalCharacter
{
	GENERATED_BODY()

public:	
	// Sets default values for this character's properties
	ABasicAICharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;	
};
