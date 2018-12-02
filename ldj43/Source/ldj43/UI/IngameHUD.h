#pragma once

#include "Characters/MainCharacter.h"
#include "UI/PlayerWidget.h"
#include "UI/SacrificeSelectorWidget.h"
#include "UI/EndGameWidget.h"

#include "GameFramework/HUD.h"
#include "IngameHUD.generated.h"

UCLASS()
class LDJ43_API AIngameHUD : public AHUD
{
	GENERATED_BODY()

private:
	AMainCharacter* _player = nullptr;
	AArenaGameState* _gamestate = nullptr;

	AIngameHUD();

	void registerToGameEvents();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> _playerWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerWidget* _playerWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> _sacrificeSelectorWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USacrificeSelectorWidget* _sacrificeSelectorWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> _endGameWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UEndGameWidget*			_endGameWidgetInstance = nullptr;

public:
	void BeginPlay() override;

	void SetWaveNumber(int number);
	void SetRoundNumber(int number);

	UFUNCTION(BlueprintCallable)
	void NewSacrifice(USacrifice* bonus1, USacrifice* malus1, USacrifice* bonus2, USacrifice* malus2);

	UFUNCTION()
	void handleEndGameGUI();
};
