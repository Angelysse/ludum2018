#include "JumpState.h"

void JumpState::onEnterState()
{
	//Do something
}

void JumpState::onExitState()
{
	//Do something
}

bool JumpState::canSwitchTo(uint8 newState)
{
	return newState == static_cast<uint8>(StateType::IDLE);
}

uint8 JumpState::getState() const
{
	return static_cast<uint8>(StateType::JUMP);
}