#pragma once

#include "Containers/UnrealString.h"

#include "ISacrifice.h"

class SEquipItem : public ISacrifice
{
	FString _itemName;

public:
	SEquipItem(AMainCharacter* chara, const FString& itemName) :
		ISacrifice(chara),
		_itemName{ itemName }
	{
	}

	void Use()
	{
		_chara->SetItem(_itemName);
	}
};