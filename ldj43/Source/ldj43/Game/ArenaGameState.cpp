#include "ArenaGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void AArenaGameState::BeginPlay()
{
	Super::BeginPlay();

	_hud = Cast<AIngameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void AArenaGameState::IncrementWave()
{
	_wave++;
	if (_hud)
		_hud->SetWaveNumber(_wave);
}

void AArenaGameState::IncrementRound()
{
	_round++;
	if (_hud)
		_hud->SetRoundNumber(_round);
}