// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaGameState.h"

#include "Engine/Engine.h"
#include "EngineGlobals.h"

//=====================
//Custom Methods

void AArenaGameState::switchToNextWave()
{
	_nextWave.Broadcast();
}

//-----------------

void AArenaGameState::switchToNextRound()
{
	_nextRound.Broadcast();
}

//-----------------

void AArenaGameState::onTakeDamage(AGlobalCharacter* hitBy)
{
	_takeDamage.Broadcast(hitBy);
}

//-----------------

void AArenaGameState::onDie(AGlobalCharacter* deadChar, AGlobalCharacter* killedBy)
{
	_die.Broadcast(deadChar, killedBy);
}

//-----------------

//=====================
//Getters

FNextWave&	AArenaGameState::getOnNextWave()
{
	return _nextWave;
}

//-----------------

FNextRound&	AArenaGameState::getOnNextRound()
{
	return _nextRound;
}

//-----------------

FTakeDamage& AArenaGameState::getOnTakeDamage()
{
	return _takeDamage;
}

//-----------------

FDie& AArenaGameState::getOnDie()
{
	return _die;
}

//-----------------