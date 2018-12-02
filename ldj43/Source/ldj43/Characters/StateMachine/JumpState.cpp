#include "JumpState.h"
#include "Characters/MainCharacter.h"

void JumpState::onEnterState()
{
	_chara->Jump();
}

void JumpState::onExitState()
{
	_chara->StopJumping();
}

bool JumpState::canSwitchTo(uint8 newState) const
{
	return newState == static_cast<uint8>(StateType::IDLE) ||
		newState == static_cast<uint8>(StateType::DEATH);
}

uint8 JumpState::getState() const
{
	return static_cast<uint8>(StateType::JUMP);
}