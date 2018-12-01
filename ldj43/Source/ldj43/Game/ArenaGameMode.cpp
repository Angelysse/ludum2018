// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaGameMode.h"

#include "EngineUtils.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"

//=====================
//Overriden Methods

void AArenaGameMode::InitGame(FString const& MapName, FString const& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	initAIManager();
}

//-----------------

void AArenaGameMode::BeginPlay()
{
	Super::BeginPlay();

	spawnWave(1);
}

//=====================
//Custom Methods

void AArenaGameMode::initAIManager()
{
	//Get a pointer to the AIManager, should iterate on only 1 object
	for (TActorIterator<AAIManager> actorItr(GetWorld()); actorItr; ++actorItr)
	{
		_aiManager = *actorItr;
		break;
	}

	if (_aiManager == nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("Missing AiManager in the level"));
}

//-----------------

void AArenaGameMode::spawnWave(uint32 nbEnemies)
{
	if (_aiManager != nullptr)
	{
		uint32 count = 0;

		while (count != nbEnemies)
		{
			if (_aiManager->spawnRandomEnemy())	//Might want to pass position as argument
			{
				count++;
			}
		}
	}
}

//-----------------