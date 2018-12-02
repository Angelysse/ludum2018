#pragma once

#include "Game/GlobalGameState.h"
#include "Characters/GlobalCharacter.h"

#include "ArenaGameState.generated.h"

DECLARE_EVENT(AArenaGameState, FNextWave);
DECLARE_EVENT(AArenaGameState, FNextRound);
DECLARE_EVENT_OneParam(AArenaGameState, FTakeDamage, AGlobalCharacter*);
DECLARE_EVENT_TwoParams(AArenaGameState, FDie, AGlobalCharacter*, AGlobalCharacter*);

UCLASS()
class LDJ43_API AArenaGameState : public AGlobalGameState
{
	GENERATED_BODY()

private:
	//Events
	FNextWave	_nextWave;
	FNextRound	_nextRound;
	FTakeDamage	_takeDamage;
	FDie		_die;

	int _round = 0;
	int _wave = 0;

	class AIngameHUD* _hud;

protected:
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float _currentTimer = 5;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
	float _maxTimer = 5;

public:
	//Custom Methods
	void switchToNextWave();
	void switchToNextRound();
	void onTakeDamage(AGlobalCharacter* hitBy);
	void onDie(AGlobalCharacter* deadChar, AGlobalCharacter* killedBy);

	//Getters
	FNextWave&		getOnNextWave();
	FNextRound&		getOnNextRound();
	FTakeDamage&	getOnTakeDamage();
	FDie&			getOnDie();
};
