#include "IdleRunState.h"

void IdleRunState::onEnterState()
{
	//Do something
}

void IdleRunState::onExitState()
{
	//Do something
}

bool IdleRunState::canSwitchTo(uint8 newState)
{
	return newState == static_cast<uint8>(StateType::ATTACK) ||
			newState == static_cast<uint8>(StateType::JUMP);
}

uint8 IdleRunState::getState() const
{
	return static_cast<uint8>(StateType::IDLE);
}