#pragma once

#include "Game/GlobalGameMode.h"
#include "ArenaGameMode.generated.h"

UCLASS()
class LDJ43_API AArenaGameMode : public AGlobalGameMode
{
	GENERATED_BODY()
	
protected:
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

	void StartPlay() override;
};