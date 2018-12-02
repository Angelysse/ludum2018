#pragma once

#include "Characters/MainCharacter.h"
#include "UI/PlayerWidget.h"

#include "GameFramework/HUD.h"
#include "IngameHUD.generated.h"

UCLASS()
class LDJ43_API AIngameHUD : public AHUD
{
	GENERATED_BODY()

private:
	AGlobalCharacter* _player = nullptr;

	AIngameHUD();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> _playerWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayerWidget* _playerWidget = nullptr;

public:
	void BeginPlay() override;

	void SetWaveNumber(int number);
	void SetRoundNumber(int number);
};
