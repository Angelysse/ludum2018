#pragma once

#include "Controllers/MainPlayerController.h"

#include "Sacrifice.h"

#include "UObject/NoExportTypes.h"
#include "InputSacrifice.generated.h"

UCLASS()
class LDJ43_API UInputSacrifice : public USacrifice
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sacrifice")
	uint8 action = static_cast<uint8>(Action::JUMP);

	void Regenerate() override
	{
	}
	void ApplyBonus(AMainCharacter* chara) override
	{
		Cast<AMainPlayerController>(chara->Controller)->enableAction(static_cast<Action>(action));
	}
	void ApplyMalus(AMainCharacter* chara) override
	{
		Cast<AMainPlayerController>(chara->Controller)->disableAction(static_cast<Action>(action));
	}
};