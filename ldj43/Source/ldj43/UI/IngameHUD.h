#pragma once

#include "Characters/MainCharacter.h"

#include "GameFramework/HUD.h"
#include "IngameHUD.generated.h"

UCLASS()
class LDJ43_API AIngameHUD : public AHUD
{
	GENERATED_BODY()
	
private:

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString waveText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString roundText;

};
