#include "DeathState.h"
#include "Characters/MainCharacter.h"

void DeathState::onEnterState()
{
}

void DeathState::onExitState()
{
}

bool DeathState::canSwitchTo(uint8 newState) const
{
	return false;
}

uint8 DeathState::getState() const
{
	return static_cast<uint8>(StateType::DEATH);
}