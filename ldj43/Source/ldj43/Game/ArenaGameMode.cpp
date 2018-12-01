#include "ArenaGameMode.h"

#include "LD/CubeActor.h"

#include "EngineUtils.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

//=====================
//Overriden Methods

void AArenaGameMode::InitGame(FString const& MapName, FString const& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	initAIManager();
	_wallsRoot = GetWorld()->SpawnActor<ACubeActor>();
}

//-----------------

void AArenaGameMode::BeginPlay()
{
	Super::BeginPlay();

	spawnWave(1);
}

//-----------------

void AArenaGameMode::StartPlay()
{
	Super::StartPlay();

	GenerateMap();
}

//=====================
//Custom Methods

void AArenaGameMode::GenerateMap()
{
	uint32 gridWidth = _mapWidth / _mapStepWidth;
	uint32 gridHeight = _mapHeight / _mapStepHeight;

	//char* map = new char[gridWidth * gridHeight]{};

	if (_wallsRoot->Children.Num())
		_wallsRoot->Children.Empty();

	// Create some big blocks.
	uint32 bigWallNum = FMath::RandRange(_mapMinWalls, _mapMaxWalls);

	for (uint32 i = 0u; i < bigWallNum; i++)
	{
	START:

		uint32 sizeX = FMath::RandRange(1, _mapMaxWallSize); uint32 sizeY = FMath::RandRange(1, _mapMaxWallSize);
		uint32 posX = FMath::RandRange(0, gridWidth); uint32 posY = FMath::RandRange(0, gridHeight);

		if (!(posX > gridWidth / 2 || posX + sizeX < gridWidth / 2 || posY > gridHeight / 2 || posY + sizeY < gridHeight / 2))
			goto START; // You know, I have slept only 2 hours... Yes life.

		//// Fill map.
		//for (uint32 j = 0u; j < sizeY; j++)
		//{
		//	for (uint32 k = 0u; k < sizeX; k++)
		//		map[posX + posY * gridWidth] = 1;
		//}

		// Spawn Block.
		auto actor = GetWorld()->SpawnActor<ACubeActor>(FVector(float(posX) - _mapWidth / 2, float(posY) - _mapHeight / 2, 270.0), FRotator::ZeroRotator);
		actor->SetActorScale3D(FVector(sizeX, sizeY, 5));
		actor->AttachToActor(_wallsRoot, FAttachmentTransformRules::KeepWorldTransform);
	}
}

//-----------------

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