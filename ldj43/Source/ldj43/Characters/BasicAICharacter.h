// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GlobalCharacter.h"
#include "BehaviorTree/BehaviorTree.h"

#include "BasicAICharacter.generated.h"

UCLASS()
class LDJ43_API ABasicAICharacter : public AGlobalCharacter
{
	GENERATED_BODY()

	protected:
		//Overriden Methods
		virtual void BeginPlay() override;

	public:
		//Variables
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
		UBehaviorTree* _botBehaviorTree = nullptr;

		//Constructors
		ABasicAICharacter();

		//Overriden Methods
		virtual void Tick(float DeltaTime) override;

		//Custom Methods
		virtual void startAttack() override;
		virtual void endAttack() override;
		virtual void endAttackCooldown() override;
		virtual bool canHit(AGlobalCharacter const* other) override;
};
