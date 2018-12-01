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

	if (_aiManager->spawnRandomEnemy())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, "C'est censé marcher");
	}
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