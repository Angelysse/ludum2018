// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAICharacter.h"


// Sets default values
ABasicAICharacter::ABasicAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void ABasicAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}