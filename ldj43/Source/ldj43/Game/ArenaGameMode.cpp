#include "ArenaGameMode.h"
#include "Engine/World.h"

#include "LD/CubeActor.h"

void AArenaGameMode::StartPlay()
{
	Super::StartPlay();

	GenerateMap();
}

void AArenaGameMode::GenerateMap()
{
	uint32 gridWidth = _mapWidth / _mapStepWidth;
	uint32 gridHeight = _mapHeight / _mapStepHeight;

	char* map = new char[gridWidth * gridHeight]{};

	// Create some big blocks.
	uint32 bigWallNum = FMath::RandRange(_mapMinWalls, _mapMaxWalls);

	for (uint32 i = 0u; i < bigWallNum; i++)
	{
		uint32 sizeX = FMath::RandRange(1, _mapMaxWallSize); uint32 sizeY = FMath::RandRange(1, _mapMaxWallSize);
		uint32 posX = FMath::RandRange(0, gridWidth); uint32 posY = FMath::RandRange(0, gridHeight);

		// Fill map.
		for (uint32 j = 0u; j < sizeY; j++)
		{
			for (uint32 k = 0u; k < sizeX; k++)
				map[posX + posY * gridWidth] = 1;
		}

		// Spawn Block.
		auto actor = GetWorld()->SpawnActor<ACubeActor>(FVector(float(posX) - _mapWidth / 2, float(posY) - _mapHeight / 2, 270.0), FRotator::ZeroRotator);
		actor->SetActorScale3D(FVector(sizeX, sizeY, 5));
	}
;}