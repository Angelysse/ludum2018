#pragma once

#include "ISacrifice.h"

#include "Contollers/MainPlayerController.h"

class SInput : public ISacrifice
{
	Action _action;
	bool _isEnable;

public:
	SStatsModify(AMainCharacter* chara, Action action, bool isEnable) :
		ISacrifice(chara),
		_action{ action },
		_isEnable{ isEnable }
	{
	}

	void Use()
	{
		Cast<AMainPlayerController>(_chara->Controller)->modifyAction(_action, _isEnable);
	}
};