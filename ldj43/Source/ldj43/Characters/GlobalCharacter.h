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
	StateMachine		_sMachine		= StateMachine(this);

	//Overriden Methods
	virtual void BeginPlay() override;

public:
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float maxHp = 100.0f;

	float hp = maxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float basicAttackPower = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float basicAttackSpeed = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float attackSpeedMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float attackCooldown = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float attackRange = 70.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool canAttack = true;

	class UMainAnimInstance*	_animInstance = nullptr;

	//Constructors
	AGlobalCharacter();

	//Overriden Methods
	virtual void Tick(float DeltaTime) override;
	
	//Custom Methods
	UFUNCTION(BlueprintCallable)
	virtual void LAttack();

	UFUNCTION(BlueprintCallable)
	virtual void RAttack();

	UFUNCTION(BlueprintCallable)
	virtual bool canHit(AGlobalCharacter const* other);

	UFUNCTION(BlueprintCallable)
	void takeDamageFrom(AGlobalCharacter const* other, float damages);

	virtual void onTakeDamageFrom(AGlobalCharacter const* other);

	virtual void onDie(AGlobalCharacter const* killedBy);

	virtual void startAttack();
	virtual void endAttack();

	UFUNCTION(BlueprintCallable)
	virtual void endAttackCooldown();

	UFUNCTION(BlueprintCallable, Category = "Player")
	uint8 GetState() const;

	UFUNCTION(BlueprintCallable)
	virtual float getAttackPower(bool isRightSlot) const;

	UFUNCTION(BlueprintCallable, Category = "Player")
	void SetState(uint8 state);

	float GetMaxHP() const;
	void SetMaxHP(float _maxHp);
};
