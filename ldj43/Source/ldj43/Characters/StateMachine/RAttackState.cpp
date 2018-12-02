#include "RAttackState.h"

#include "Characters/GlobalCharacter.h"

void RAttackState::onEnterState()
{
	_chara->canAttack = false;
	_chara->startAttack();
}

void RAttackState::onExitState()
{
	_chara->endAttack();
}

bool RAttackState::canSwitchTo(uint8 newState) const
{
	return newState == static_cast<uint8>(StateType::IDLE) ||
		newState == static_cast<uint8>(StateType::DEATH);
}

uint8 RAttackState::getState() const
{
	return static_cast<uint8>(StateType::RATTACK);
}