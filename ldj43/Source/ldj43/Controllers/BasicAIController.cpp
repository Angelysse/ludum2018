// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAIController.h"

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

	//ADwarfCharacter* bot = Cast<ADwarfCharacter>(InPawn);

	//Start behavior
	/*if (bot != nullptr && bot->m_bot_behavior != nullptr)
	{
		RunBehaviorTree(bot->m_bot_behavior);

		initDefaultBBValues();
	}*/
}

//=====================
//Custom Methods

void ABasicAIController::initDefaultBBValues()
{
	//Set target (player 0)

	//Set activation
}

//-----------------