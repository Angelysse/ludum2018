#include "AttackState.h"

void AttackState::onEnterState()
{
	//Do something
}

void AttackState::onExitState()
{
	//Do something
}

bool AttackState::canSwitchTo(uint8 newState) const
{
	return newState == static_cast<uint8>(StateType::IDLE);
}

uint8 AttackState::getState() const
{
	return static_cast<uint8>(StateType::ATTACK);
}