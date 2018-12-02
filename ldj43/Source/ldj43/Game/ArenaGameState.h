#pragma once

#include "Game/GlobalGameState.h"
#include "UI/IngameHUD.h"

#include "ArenaGameState.generated.h"

UCLASS()
class LDJ43_API AArenaGameState : public AGlobalGameState
{
	GENERATED_BODY()

private:
	int _wave = 0;
	int _round = 0;

	float _currentTimer = 0;
	float _maxTimer = 5;
	bool _isSelecting = false;

	AIngameHUD* _hud;

public:
	void BeginPlay() override;

	void IncrementWave();
	void IncrementRound();
};
