// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BasicAIController.generated.h"

/**
 * 
 */
UCLASS()
class LDJ43_API ABasicAIController : public AAIController
{
	GENERATED_BODY()
	
	private:
		//Constructors
		ABasicAIController(FObjectInitializer const& objectInitializer);

		//Overriden Methods
		virtual void Possess(APawn* InPawn) override;

		//Custom Methods

	public:
		//Custom Methods
		void	initDefaultBBValues();
		void	setTargetPawn(APawn* targetPawn);
		void	setIsActive(bool isActive);
		void	setCanAttack(bool canAttack);
		void	setIsAttacking(bool isAttacking);
};
