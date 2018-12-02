// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Core/Public/Math/Vector.h"
#include "GameFramework/Actor.h"
#include "Characters/BasicAICharacter.h"

#include "AIManager.generated.h"

UCLASS()
class LDJ43_API AAIManager : public AActor
{
	GENERATED_BODY()

private:
	//Variables
	uint32	_totalFrequency;
	bool	_isValid;

	TArray<ABasicAICharacter*>	_bots;

	//Custom Methods
	void computeEnemySpawnFrequencies();
	void registerToGameEvents();

	UFUNCTION()
	void disableAllAI();

protected:
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	TArray<TSubclassOf<ABasicAICharacter>>	_enemyTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	TArray<uint8>							_enemySpawnFrequencies;

	//Overriden Methods
	virtual void BeginPlay() override;

	//Custom Methods
	FVector generateRandomLocation() const;

public:	
	//Constructors
	AAIManager();

	//Overriden Methods
	virtual void Tick(float DeltaTime) override;

	//Custom Methods
	bool spawnEnemy(TSubclassOf<ABasicAICharacter>& enemyType);
	bool spawnRandomEnemy();
	void spawnWave(uint32 nbEnemies);
	
	bool areAllAIDead() const;

	UFUNCTION()
	void handleBotDeath(AGlobalCharacter* deadChar, AGlobalCharacter* other);
};
