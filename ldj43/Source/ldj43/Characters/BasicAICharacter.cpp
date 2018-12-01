// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAICharacter.h"

//============================
//Constructors

ABasicAICharacter::ABasicAICharacter():
	AGlobalCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

//============================
//Overriden Methods

void ABasicAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

//--------------------------

void ABasicAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//============================
//Custom Methods