// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAICharacter.h"

#include "Controllers/BasicAIController.h"
#include "MainCharacter.h"

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

void ABasicAICharacter::startAttack()
{
	AGlobalCharacter::startAttack();

	ABasicAIController* controller = Cast<ABasicAIController>(GetController());
	if (controller != nullptr)
	{
		controller->setCanAttack(false);
		controller->setIsAttacking(true);
	}
}

//--------------------------

void ABasicAICharacter::endAttack()
{
	AGlobalCharacter::endAttack();

	ABasicAIController* controller = Cast<ABasicAIController>(GetController());
	if (controller != nullptr)
	{
		controller->setIsAttacking(false);
	}
}

//--------------------------

void ABasicAICharacter::endAttackCooldown()
{
	AGlobalCharacter::endAttackCooldown();

	ABasicAIController* controller = Cast<ABasicAIController>(GetController());
	if (controller != nullptr)
	{
		controller->setCanAttack(true);
	}
}

//--------------------------

bool ABasicAICharacter::canHit(AGlobalCharacter const* other)
{
	return Cast<AMainCharacter>(other) != nullptr;
}