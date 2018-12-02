#include "IngameHUD.h"

#include "../Game/ArenaGameState.h"

#include "Kismet/GameplayStatics.h"

AIngameHUD::AIngameHUD()
{

}

void AIngameHUD::BeginPlay()
{
	Super::BeginPlay();

	// Get player reference
	_player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (_playerWidgetClass && _player != nullptr)
	{
		// Create and display Widgets
		_playerWidget = CreateWidget<UPlayerWidget>(GetWorld(), _playerWidgetClass);
		_playerWidget->SetPlayer(_player);
		_playerWidget->AddToViewport();

		SetWaveNumber(0);
		SetRoundNumber(0);
	}

	_gamestate = Cast<AArenaGameState>(GetWorld()->GetGameState());

	if (_sacrificeSelectorWidgetClass && _player != nullptr && _gamestate != nullptr)
	{
		// Create and display Widgets
		_sacrificeSelectorWidget = CreateWidget<USacrificeSelectorWidget>(GetWorld(), _sacrificeSelectorWidgetClass);
		_sacrificeSelectorWidget->SetPlayer(_player);
		_sacrificeSelectorWidget->SetGameState(_gamestate);
		_sacrificeSelectorWidget->AddToViewport();
		_sacrificeSelectorWidget->SetVisibility(ESlateVisibility::Hidden);

		SetWaveNumber(0);
		SetRoundNumber(0);
	}

	if (_endGameWidgetClass && _player != nullptr && _gamestate != nullptr)
	{
		// Create and display Widgets
		_endGameWidgetInstance = CreateWidget<UEndGameWidget>(GetWorld(), _endGameWidgetClass);
		_endGameWidgetInstance->AddToViewport();
		_endGameWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	}

	registerToGameEvents();
}

void AIngameHUD::registerToGameEvents()
{
	AArenaGameState* gameState = GetWorld()->GetGameState<AArenaGameState>();

	if (gameState != nullptr)
	{
		//EndGame
		gameState->getEndGame().AddUFunction(this, "handleEndGameGUI");
	}
}

void AIngameHUD::SetWaveNumber(int number)
{
	_playerWidget->SetWave(number);
}

void AIngameHUD::SetRoundNumber(int number)
{
	_playerWidget->SetRound(number);
}

void AIngameHUD::NewSacrifice(USacrifice* bonus1, USacrifice* malus1, USacrifice* bonus2, USacrifice* malus2)
{
	_sacrificeSelectorWidget->Activate(bonus1, malus1, bonus2, malus2);
	_sacrificeSelectorWidget->SetVisibility(ESlateVisibility::Visible);
}

void AIngameHUD::handleEndGameGUI()
{
	if (_endGameWidgetInstance != nullptr)
	{
		_endGameWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		_endGameWidgetInstance->handleApparition();
	}
}