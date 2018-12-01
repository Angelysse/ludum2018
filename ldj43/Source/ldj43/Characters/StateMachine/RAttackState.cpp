#include "RAttackState.h"

void RAttackState::onEnterState()
{
	//Do something
}

void RAttackState::onExitState()
{
	//Do something
}

bool RAttackState::canSwitchTo(uint8 newState) const
{
	return newState == static_cast<uint8>(StateType::IDLE);
}

uint8 RAttackState::getState() const
{
	return static_cast<uint8>(StateType::RATTACK);
}