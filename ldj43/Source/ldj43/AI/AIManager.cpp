// Fill out your copyright notice in the Description page of Project Settings.

#include "AIManager.h"
#include "../Game/ArenaGameState.h"
#include "../Game/ArenaGameMode.h"

#include "Engine/World.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

//============================
//Constructors

AAIManager::AAIManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

//============================
//Overriden Methods

void AAIManager::BeginPlay()
{
	Super::BeginPlay();

	_isValid = (_enemyTypes.Num() == _enemySpawnFrequencies.Num());

	if (!_isValid)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("enemyType.Num() != enemySpawnFreq.Num()"));
	}
	
	computeEnemySpawnFrequencies();
}

//--------------------------

void AAIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//============================
//Custom Methods

//void AAIManager::registerToGameEvents()
//{
//	AArenaGameState* gameState = GetWorld()->GetGameState<AArenaGameState>();
//	
//	if (gameState != nullptr)
//	{
//		//Dead character
//		gameState->getOnDie().AddUFunction(this, "handleBotDeath");
//	}
//}

//--------------------------

void AAIManager::handleBotDeath(AGlobalCharacter* deadChar, AGlobalCharacter* other)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("HandleBotDeath"));

	for (int32 index = 0; index < _bots.Num(); index++)
	{
		if (_bots[index] == deadChar)
		{
			_bots.RemoveAt(index);
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Removed"));

			AArenaGameMode* gameMode = Cast<AArenaGameMode>(GetWorld()->GetAuthGameMode());
			if (gameMode != nullptr)
			{
				gameMode->checkRoundProgression(deadChar, other);
			}

			break;
		}
	}
}

//--------------------------

void AAIManager::computeEnemySpawnFrequencies()
{
	_totalFrequency = 0;

	for (uint8 value : _enemySpawnFrequencies)
	{
		_totalFrequency += value;
	}
}

//--------------------------

FVector AAIManager::generateRandomLocation() const
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	uint32		randomSide = FMath::RandRange(0, 1);

	if (player != nullptr)
	{
		FVector position = player->GetActorLocation();

		if (randomSide)
		{
			position.X = (position.X > 0) ? -4600.0f : 4600.0f;
			position.Y = FMath::RandRange(-4600.0f, 4600.0f);
		}
		else
		{
			position.X = FMath::RandRange(-4600.0f, 4600.0f);
			position.Y = (position.Y > 0) ? -4600.0f : 4600.0f;
		}

		return position;
	}

	return FVector(-4600.0f, -4600.0f, 50.0f);
}

//--------------------------

bool AAIManager::spawnEnemy(TSubclassOf<ABasicAICharacter>& enemyType)
{
	FActorSpawnParameters	spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	ABasicAICharacter* spawnedBot = GetWorld()->SpawnActor<ABasicAICharacter>(enemyType.Get(), generateRandomLocation(), FRotator::ZeroRotator, spawnParams);

	if (spawnedBot != nullptr)
	{
		_bots.Add(spawnedBot);

		return true;
	}

	return false;
}

//--------------------------

bool AAIManager::spawnRandomEnemy()
{
	if (_enemyTypes.Num() > 0 && _enemySpawnFrequencies.Num() > 0)
	{
		int32 currMin = 0;
		int32 currMax = 0;

		int32 random = FMath::RandRange(0, _totalFrequency - 1);

		for (int32 index = 0; index < _enemyTypes.Num(); index++)
		{
			currMax += _enemySpawnFrequencies[index];

			if (random >= currMin && random < currMax)
			{
				return spawnEnemy(_enemyTypes[index]);
			}

			currMin = currMax;
		}
	}

	return false;
}

//--------------------------

void AAIManager::spawnWave(uint32 nbEnemies)
{
	uint32 count = 0;

	while (count != nbEnemies)
	{
		if (spawnRandomEnemy())	//Might want to pass position as argument
		{
			count++;
		}
	}
}

//--------------------------

bool AAIManager::areAllAIDead() const
{
	return !_bots.Num();
}