#include "ArenaGameMode.h"

#include "ArenaGameState.h"
#include "LD/CubeActor.h"
#include "UI/IngameHUD.h"

#include "EngineUtils.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/TimerManager.h"

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

void AArenaGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float time = UGameplayStatics::GetGlobalTimeDilation(GetWorld());

	if (!FMath::IsNearlyEqual(time, _targetTime))
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), FMath::Lerp(_targetTime, _prevTime, DeltaSeconds * time));
}

//-----------------

void AArenaGameMode::StartPlay()
{
	Super::StartPlay();

	GenerateMap();
}

//-----------------

void AArenaGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(_waveTimeOutHandle);
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
		actor->ScaleWall(FVector(sizeX, sizeY, 5));
		actor->AttachToActor(_wallsRoot, FAttachmentTransformRules::KeepWorldTransform);
	}
}

//-----------------

void AArenaGameMode::GenerateSacrifice()
{
	uint32 bIndex1 = FMath::RandRange(0, sacrifices.Num() - 1);
	uint32 mIndex1 = FMath::RandRange(0, sacrifices.Num() - 1);

	while(mIndex1 == bIndex1)
		mIndex1 = FMath::RandRange(0, sacrifices.Num() - 1);

	uint32 bIndex2 = FMath::RandRange(0, sacrifices.Num() - 1);
	uint32 mIndex2 = FMath::RandRange(0, sacrifices.Num() - 1);

	while (mIndex2 == bIndex2)
		mIndex2 = FMath::RandRange(0, sacrifices.Num() - 1);

	sacrifices[bIndex1].GetDefaultObject()->Regenerate();
	sacrifices[mIndex1].GetDefaultObject()->Regenerate();
	sacrifices[bIndex2].GetDefaultObject()->Regenerate();
	sacrifices[mIndex2].GetDefaultObject()->Regenerate();

	if(sacrificeSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), sacrificeSound, FVector()); // no attenuation ;)

	Cast<AIngameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())->
		NewSacrifice(sacrifices[bIndex1].GetDefaultObject(), sacrifices[mIndex1].GetDefaultObject(),
			sacrifices[bIndex2].GetDefaultObject(), sacrifices[mIndex2].GetDefaultObject());

	_prevTime = _targetTime;
	_targetTime = slowTime;
}

//-----------------

void AArenaGameMode::ResetTimeDelation()
{
	_prevTime = _targetTime;
	_targetTime = 1.0f;
}
void AArenaGameMode::TriggerSacrifice(float multiplier)
{
	if (FMath::FRandRange(0.0f, 1.0f) < sacrificeRate * multiplier)
		GenerateSacrifice();
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
	AArenaGameState* gameState = Cast<AArenaGameState>(GameState);
	if (gameState != nullptr)
	{
		_aiManager->spawnWave(_currentRound.nextWave());
		GetWorld()->GetTimerManager().SetTimer(_waveTimeOutHandle, this, &AArenaGameMode::handleNewWaveWithCheck, _waveTimeoutDelay, false);
	}
}

//-----------------

void AArenaGameMode::handleNewWaveWithCheck()
{
	if (!_currentRound.isLastWave())
	{
		AArenaGameState* gameState = Cast<AArenaGameState>(GameState);
		if (gameState != nullptr)
		{
			gameState->switchToNextWave();
		}
	}
}

//-----------------

void AArenaGameMode::checkRoundProgression(AGlobalCharacter* deadChar, AGlobalCharacter* killedBy)
{
	AArenaGameState*	gameState = Cast<AArenaGameState>(GameState);

	if (gameState != nullptr)
	{
		//Wave finished
		if (_aiManager != nullptr && _aiManager->areAllAIDead())
		{
			//Next round
			if (_currentRound.isLastWave())
				gameState->switchToNextRound();
			else	//Next wave
				gameState->switchToNextWave();
		}
	}
}