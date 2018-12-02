#pragma once

#include "Game/GlobalGameMode.h"
#include "AI/AIManager.h"

#include "Sacrifices/SacrificeIncludes.h"

#include "ArenaGameMode.generated.h"

UCLASS()
class LDJ43_API AArenaGameMode : public AGlobalGameMode
{
	GENERATED_BODY()

	private:
		//Variables
		AAIManager*		_aiManager = nullptr;

		AActor* _wallsRoot = nullptr;

		FTimerHandle _spawnHandle;

		//Custom Methods
		void initAIManager();
		
		float targetTime = 1.0f;

	public:
		void Tick(float DeltaSeconds) override;

		//Overriden Methods
		virtual void InitGame(FString const& MapName, FString const& Options, FString& ErrorMessage) override;
		virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	TArray<TSubclassOf<USacrifice>> sacrifices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
	float slowTime = 0.1f;

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

	void GenerateMap();
	void GenerateSacrifice();
	void ResetTimeDelation();

	void StartPlay() override;
};