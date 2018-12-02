#include "ArenaGameMode.h"

#include "LD/CubeActor.h"

#include "EngineUtils.h"
#include "EngineGlobals.h"
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
	uint32 gridWidth = _mapWidth / _mapStepWidth; uint32 gridHeight = _mapHeight / _mapStepHeight;
	uint32 midX = gridWidth / 2; uint32 midY = gridHeight / 2;

	if (_wallsRoot->Children.Num())
		_wallsRoot->Children.Empty();

	// Create some big blocks.
	uint32 bigWallNum = FMath::RandRange(_mapMinWalls, _mapMaxWalls);

	for (uint32 i = 0u; i < bigWallNum; i++)
	{
	START:

		uint32 sizeX = FMath::RandRange(1, _mapMaxWallSize); uint32 sizeY = FMath::RandRange(1, _mapMaxWallSize);
		uint32 posX = FMath::RandRange(0, gridWidth); uint32 posY = FMath::RandRange(0, gridHeight);

		if (!(posX - 100 * sizeX / 2 > midX + 100 || posX + 100 * sizeX / 2 < midX - 100 ||
			posY - 100 * sizeY / 2 > midY + 100 || posY + 100 * sizeY / 2 < midY - 100))
			goto START; // You know, I have slept only 2 hours... Yes life.

		// Spawn Block.
		auto actor = GetWorld()->SpawnActor<ACubeActor>(FVector(float(posX) - midX, float(posY) - midY, 270.0), FRotator::ZeroRotator);
		actor->SetActorScale3D(FVector(sizeX, sizeY, 5));
		actor->AttachToActor(_wallsRoot, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void AArenaGameMode::GenerateSacrifice()
{

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