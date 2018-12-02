#pragma once

#include "Sacrifices/Bonus.h"
#include "Sacrifices/Malus.h"

#include "UObject/NoExportTypes.h"
#include "Sacrifice.generated.h"

UCLASS(Blueprintable)
class LDJ43_API USacrifice : public UObject, public IBonus, public IMalus
{
	GENERATED_BODY()

public:
	void Regenerate() override {}
	void ApplyBonus(AMainCharacter* chara) override {}
	void ApplyMalus(AMainCharacter* chara) override {}
};