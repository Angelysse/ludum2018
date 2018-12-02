#include "LAttackState.h"

#include "Characters/GlobalCharacter.h"

void LAttackState::onEnterState()
{
	_chara->canAttack = false;
	_chara->startAttack();
}

void LAttackState::onExitState()
{
	_chara->endAttack();
}

bool LAttackState::canSwitchTo(uint8 newState) const
{
	return newState == static_cast<uint8>(StateType::IDLE);
}

uint8 LAttackState::getState() const
{
	return static_cast<uint8>(StateType::LATTACK);
}