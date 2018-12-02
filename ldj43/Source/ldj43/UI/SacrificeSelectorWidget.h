#pragma once

#include "Blueprint/UserWidget.h"
#include "Sacrifices/Sacrifice.h"
#include "Game/ArenaGameState.h"
#include "SacrificeSelectorWidget.generated.h"

UCLASS()
class LDJ43_API USacrificeSelectorWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AArenaGameState* _gamestate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AMainCharacter* _mainCharacter;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void Activate(USacrifice* bonus1, USacrifice* malus1, USacrifice* bonus2, USacrifice* malus2);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnExpired();

	void SetPlayer(AMainCharacter* player) { _mainCharacter = player; }
	void SetGameState(AArenaGameState* gs) { _gamestate = gs; }
};
