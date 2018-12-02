#include "ArenaGameMode.h"

#include "ArenaGameState.h"
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

	registerToGameEvents();
	handleNewRound();
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

void AArenaGameMode::registerToGameEvents()
{
	AArenaGameState*	gameState = Cast<AArenaGameState>(GameState);

	if (gameState != nullptr)
	{
		//Next round
		gameState->getOnNextRound().AddUFunction(this, "handleNewRound");

		//Next wave
		gameState->getOnNextWave().AddUFunction(this, "handleNewWave");
	}
}

//-----------------

void AArenaGameMode::handleNewRound()
{
	_currentRound.nextRound();
	handleNewWave();
}

//-----------------

void AArenaGameMode::handleNewWave()
{
	uint32 nbBots = _currentRound.nextWave();
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, "Spawn " + FString::SanitizeFloat(nbBots));
	_aiManager->spawnWave(nbBots);
}

//-----------------

void AArenaGameMode::checkRoundProgression(AGlobalCharacter* deadChar, AGlobalCharacter* killedBy)
{
	AArenaGameState*	gameState = Cast<AArenaGameState>(GameState);

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, "checkRound");

	if (gameState != nullptr)
	{
		//Wave finished
		if (_aiManager != nullptr && _aiManager->areAllAIDead())
		{
			//Next round
			if (_currentRound.isLastWave())
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, "nextRound");
				gameState->switchToNextRound();
			}
			else	//Next wave
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Emerald, "nextWave");
				gameState->switchToNextWave();
			}
		}
	}
}