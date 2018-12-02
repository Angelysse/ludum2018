#pragma once

#include "Characters/MainCharacter.h"

class ISacrifice
{
protected:
	AMainCharacter* _chara = nullptr;

public:
	ISacrifice(AMainCharacter* chara) : _chara{ chara }
	{
	}

	virtual void Use() = 0;
};