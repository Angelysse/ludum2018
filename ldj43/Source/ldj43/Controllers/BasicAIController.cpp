// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAIController.h"

#include "Characters/BasicAICharacter.h"

#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Classes/BehaviorTree/BlackboardComponent.h"

//=====================
//Constructors

ABasicAIController::ABasicAIController(FObjectInitializer const& objectInitializer):
	Super(objectInitializer)
{
	//Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
}

//=====================
//Overriden Methods

void ABasicAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	ABasicAICharacter* bot = Cast<ABasicAICharacter>(InPawn);

	//Start behavior
	if (bot != nullptr && bot->_botBehaviorTree != nullptr)
	{
		RunBehaviorTree(bot->_botBehaviorTree);

		initDefaultBBValues();

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, "RIP");
	}
}

//=====================
//Custom Methods

void ABasicAIController::initDefaultBBValues()
{
	//Get Player 0
	APawn* playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (playerPawn != nullptr)
	{
		setTargetPawn(playerPawn);
	}

	setIsActive(true);
	setCanAttack(true);
	setIsAttacking(false);
}

//-----------------

void ABasicAIController::setTargetPawn(APawn* targetPawn)
{
	Blackboard->SetValueAsObject(TEXT("Target"), targetPawn);
}

//-----------------

void ABasicAIController::setIsActive(bool isActive)
{
	Blackboard->SetValueAsBool(TEXT("IsActive"), isActive);
}

//-----------------

void ABasicAIController::setCanAttack(bool canAttack)
{
	Blackboard->SetValueAsBool(TEXT("CanAttack"), canAttack);
}

//-----------------

void ABasicAIController::setIsAttacking(bool isAttacking)
{
	Blackboard->SetValueAsBool(TEXT("IsAttacking"), isAttacking);
}