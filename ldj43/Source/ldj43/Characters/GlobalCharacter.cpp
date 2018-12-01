// Fill out your copyright notice in the Description page of Project Settings.

#include "GlobalCharacter.h"


// Sets default values
AGlobalCharacter::AGlobalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGlobalCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGlobalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGlobalCharacter::LAttack()
{
	if (!_isAttacking)
	{
		_isAttacking = true;

		//_isAttacking = false on end animation
	}
}

void AGlobalCharacter::RAttack()
{
	if (!_isAttacking)
	{
		_isAttacking = true;

		//_isAttacking = false on end animation
	}
}

void AGlobalCharacter::SetMaxHP(float _maxHp)
{
	maxHp = _maxHp;

	if (hp > maxHp)
		hp = maxHp;
}