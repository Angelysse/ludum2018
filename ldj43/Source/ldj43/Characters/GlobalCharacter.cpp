// Fill out your copyright notice in the Description page of Project Settings.

#include "GlobalCharacter.h"

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

uint8 AGlobalCharacter::GetState() const
{
	return _sMachine.getState();
}

void AGlobalCharacter::SetMaxHP(float _maxHp)
{
	maxHp = _maxHp;

	if (hp > maxHp)
		hp = maxHp;
}