// Fill out your copyright notice in the Description page of Project Settings.

#include "GlobalCharacter.h"

#include "EngineGlobals.h"
#include "Engine/Engine.h"

AGlobalCharacter::AGlobalCharacter():
	_sMachine { this }
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGlobalCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	_sMachine.switchTo(StateType::IDLE);
}

// Called every frame
void AGlobalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGlobalCharacter::LAttack()
{
	_sMachine.switchTo(StateType::LATTACK);
}

void AGlobalCharacter::RAttack()
{
	_sMachine.switchTo(StateType::RATTACK);
}

bool AGlobalCharacter::canHit(AGlobalCharacter const* other)
{
	//Can't hit by default
	return false;
}

void AGlobalCharacter::takeDamageFrom(AGlobalCharacter const* other, float damages)
{
	if (hp > 0)
	{
		hp -= damages;

		onTakeDamageFrom(other);

		if (hp <= 0)
		{
			onDie(other);
		}
	}
	
}

void AGlobalCharacter::onTakeDamageFrom(AGlobalCharacter const* other)
{
	//Default behavior does nothing special
}

void AGlobalCharacter::onDie(AGlobalCharacter const* killedBy)
{
	//Switch to death state here
}

void AGlobalCharacter::startAttack()
{
	//Default behavior does nothing special
}

void AGlobalCharacter::endAttack()
{
	//Default behavior does nothing special
}

void AGlobalCharacter::endAttackCooldown()
{
	canAttack = true;
}

uint8 AGlobalCharacter::GetState() const
{
	return _sMachine.getState();
}

float AGlobalCharacter::getAttackPower(bool isRightSlot) const
{
	return basicAttackPower;
}

void AGlobalCharacter::SetState(uint8 state)
{
	_sMachine.switchTo(static_cast<StateType>(state));
}

void AGlobalCharacter::SetMaxHP(float _maxHp)
{
	maxHp = _maxHp;

	if (hp > maxHp)
		hp = maxHp;
}