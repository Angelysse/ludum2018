#include "IngameHUD.h"

#include "Kismet/GameplayStatics.h"

AIngameHUD::AIngameHUD()
{

}

void AIngameHUD::BeginPlay()
{
	Super::BeginPlay();

	// Get player reference
	_player = Cast<AGlobalCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (_playerWidgetClass && _player != nullptr)
	{
		// Create and display Widgets
		_playerWidget = CreateWidget<UPlayerWidget>(GetWorld(), _playerWidgetClass);
		_playerWidget->SetPlayer(_player);
		_playerWidget->AddToViewport();

		SetWaveNumber(0);
		SetRoundNumber(0);
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
