#pragma once

#include "Characters/MainCharacter.h"

#include "UObject/Interface.h"
#include "Bonus.generated.h"

UINTERFACE(MinimalAPI)
class UBonus : public UInterface
{
	GENERATED_BODY()
};

class LDJ43_API IBonus
{
	GENERATED_BODY()

public:
	
	virtual void Regenerate() = 0;
	virtual void ApplyBonus(AMainCharacter* chara) = 0;
};