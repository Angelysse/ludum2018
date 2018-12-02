// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAICharacter.h"

#include "Controllers/BasicAIController.h"
#include "MainCharacter.h"
#include "Game/ArenaGameMode.h"

#include "EngineGlobals.h"
#include "Engine/Engine.h"

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

//--------------------------

void ABasicAICharacter::onDie(AGlobalCharacter* deadChar, AGlobalCharacter* killedBy)
{
	AGlobalCharacter::onDie(deadChar, killedBy);

	if (deadChar == this)
	{
		ABasicAIController* controller = Cast<ABasicAIController>(GetController());
		if (controller != nullptr)
		{
			controller->setIsActive(false);
		}

		AArenaGameMode* gameMode = Cast<AArenaGameMode>(GetWorld()->GetAuthGameMode());
		if (gameMode != nullptr)
		{
			gameMode->_aiManager->handleBotDeath(deadChar, killedBy);
		}
	}
}

//--------------------------