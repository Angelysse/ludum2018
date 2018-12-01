// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StateMachine/StateMachine.h"

#include "GlobalCharacter.generated.h"

UCLASS()
class LDJ43_API AGlobalCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	//Variables
	StateMachine	_sMachine = StateMachine(this);

	//Overriden Methods
	virtual void BeginPlay() override;

public:
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float maxHp = 100.0f;

	float hp = maxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float basicAttackPower = 1.0f;

	//Constructors
	AGlobalCharacter();

	//Overriden Methods
	virtual void Tick(float DeltaTime) override;
	
	//Custom Methods
	virtual void LAttack();
	virtual void RAttack();

	UFUNCTION(BlueprintCallable, Category = "Player")
	uint8 GetState() const;
	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetState(uint8 state);

	void SetMaxHP(float _maxHp);
};
