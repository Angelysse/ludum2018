// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"


#include "GlobalCharacter.generated.h"

UCLASS()
class LDJ43_API AGlobalCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	//Overriden Methods
	virtual void BeginPlay() override;

public:
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float maxHp = 100.0f;

	float hp = maxHp;

	//Constructors
	AGlobalCharacter();

	//Overriden Methods
	virtual void Tick(float DeltaTime) override;
	
	//Custom Methods
	virtual void LAttack();
	virtual void RAttack();

	void SetMaxHP(float _maxHp);
};
