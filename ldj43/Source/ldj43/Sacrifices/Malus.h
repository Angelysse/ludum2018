#pragma once

#include "Characters/MainCharacter.h"

#include "UObject/Interface.h"
#include "Malus.generated.h"

UINTERFACE(MinimalAPI)
class UMalus : public UInterface
{
	GENERATED_BODY()
};

class LDJ43_API IMalus
{
	GENERATED_BODY()

public:

	virtual void Regenerate() = 0;
	virtual void ApplyMalus(AMainCharacter* chara) = 0;
};
