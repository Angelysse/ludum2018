#pragma once

#include "ISacrifice.h"

class SStatsModify : public ISacrifice
{
	float _addHpMax;
	float _addAttackSpeed;

public:
	SStatsModify(AMainCharacter* chara, float addHpMax, float addAttackSpeed) :
		ISacrifice(chara),
		_addHpMax{ addHpMax },
		_addAttackSpeed{ addAttackSpeed }
	{
	}

	void Use()
	{
		_chara->SetMaxHp(_chara->GetMaxHP() + _addHpMax);
		//_chara->AttackSpeedMult = 
	}
};