#pragma once

#include "Containers/UnrealString.h"

#include "ISacrifice.h"

class SEquipWeapon : public ISacrifice
{
	FString _weaponName;
	bool _isRight;

public:
	SEquipWeapon(AMainCharacter* chara, const FString& weaponName, bool isRight = false) :
		ISacrifice(chara),
		_weaponName{ weaponName }
		_isRight{ isRight }
	{
	}

	void Use()
	{
		_chara->SetWeapon(_weaponName, _isRight);
	}
};