#pragma once

#include "Blueprint/UserWidget.h"
#include "Characters/MainCharacter.h"
#include "PlayerWidget.generated.h"

UCLASS()
class LDJ43_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AGlobalCharacter* _player;
	
public:
	void SetPlayer(AMainCharacter* player);

	UFUNCTION(BlueprintImplementableEvent)
	void SetRound(int round);

	UFUNCTION(BlueprintImplementableEvent)
	void SetWave(int wave);
};
