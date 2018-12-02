#include "ArenaGameMode.h"

#include "LD/CubeActor.h"

#include "EngineUtils.h"
#include "EngineGlobals.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

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

	_aiManager->spawnWave(20);
}

void AArenaGameMode::Tick(float DeltaSeconds)
{
	float time = UGameplayStatics::GetGlobalTimeDilation(GetWorld());

	if (!FMath::IsNearlyEqual(time, targetTime))
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), FMath::Lerp(slowTime, targetTime, DeltaSeconds * FMath::Sqrt(time)));
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
		actor->ScaleWall(FVector(sizeX, sizeY, 5));
		actor->AttachToActor(_wallsRoot, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void AArenaGameMode::GenerateSacrifice()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.4);

	uint32 bIndex1 = FMath::RandRange(0, sacrifices.Num() - 1);
	uint32 mIndex1 = FMath::RandRange(0, sacrifices.Num() - 1);

	while(mIndex1 == bIndex1)
		mIndex1 = FMath::RandRange(0, sacrifices.Num() - 1);

	uint32 bIndex2 = FMath::RandRange(0, sacrifices.Num() - 1);
	uint32 mIndex2 = FMath::RandRange(0, sacrifices.Num() - 1);

	while (mIndex2 == bIndex2)
		mIndex2 = FMath::RandRange(0, sacrifices.Num() - 1);

	targetTime = slowTime;
}

void AArenaGameMode::ResetTimeDelation()
{
	targetTime = 1.0f;
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