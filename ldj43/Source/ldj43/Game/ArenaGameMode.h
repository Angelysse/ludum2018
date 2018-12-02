#pragma once

#include "Game/GlobalGameMode.h"
#include "AI/AIManager.h"
#include "ArenaRound.h"
#include "Characters/GlobalCharacter.h"

#include "Sacrifices/SacrificeIncludes.h"

#include "ArenaGameMode.generated.h"

UCLASS()
class LDJ43_API AArenaGameMode : public AGlobalGameMode
{
	GENERATED_BODY()

private:
	//Variables
	AActor*			_wallsRoot = nullptr;
	ArenaRound		_currentRound;

	FTimerHandle	_waveTimeOutHandle;

	//Custom Methods
	void initAIManager();
	void registerToGameEvents();
	void handleNewWaveWithCheck();

	UFUNCTION()
	void handleNewRound();

	UFUNCTION()
	void handleNewWave();
		
	float _targetTime = 1.0f;
	float _prevTime = 1.0f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float sacrificeRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	TArray<TSubclassOf<USacrifice>> sacrifices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	float slowTime = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	int _mapMaxWallSize = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	int _mapMinWalls = 25;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	int _mapMaxWalls = 125;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	int _mapWidth = 9000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	int _mapHeight = 9000;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	float _mapStepWidth = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	float _mapStepHeight = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _waveTimeoutDelay = 20.0f;

public:
	void Tick(float DeltaSeconds) override;

	//Overriden Methods
	virtual void InitGame(FString const& MapName, FString const& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	void GenerateMap();
	void GenerateSacrifice();
	void ResetTimeDelation();

	UFUNCTION(BlueprintCallable)
	void TriggerSacrifice(float multiplier = 1.0f);

	void StartPlay() override;

	//Variables
	AAIManager*		_aiManager = nullptr;

	//Custom Methods
	UFUNCTION()
	void checkRoundProgression(AGlobalCharacter* deadChar, AGlobalCharacter* killedBy);

	UFUNCTION(BlueprintCallable)
	int GetCurrentRound() { return _currentRound.roundNumber; }
	UFUNCTION(BlueprintCallable)
	int GetCurrentWave() { return _currentRound.currentWave; }
	UFUNCTION(BlueprintCallable)
	int GetMaxWave() { return _currentRound.totalWaves; }

};