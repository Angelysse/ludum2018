// Fill out your copyright notice in the Description page of Project Settings.

#include "AIManager.h"

#include "Engine/World.h"
#include "EngineGlobals.h"
#include "Engine.h"

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

void AAIManager::computeEnemySpawnFrequencies()
{
	_totalFrequency = 0;

	for (uint8 value : _enemySpawnFrequencies)
	{
		_totalFrequency += value;
	}
}

//--------------------------

bool AAIManager::spawnEnemy(TSubclassOf<ABasicAICharacter>& enemyType)
{
	FActorSpawnParameters	spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	FTransform				transform(GetTransform());

	ABasicAICharacter* spawnedBot = Cast<ABasicAICharacter>(GetWorld()->SpawnActor(enemyType.Get(), &transform, spawnParams));

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