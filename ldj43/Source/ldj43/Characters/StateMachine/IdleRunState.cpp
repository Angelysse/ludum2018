#include "IdleRunState.h"
#include "Engine/World.h"
#include "Game/GlobalPlayerState.h"
#include "Characters/MainCharacter.h"

void IdleRunState::onEnterState()
{
	//Do something
}

void IdleRunState::onExitState()
{
	//Do something
}

bool IdleRunState::canSwitchTo(uint8 newState) const
{
	return (newState == static_cast<uint8>(StateType::JUMP) && Cast<AGlobalPlayerState>(_chara->PlayerState)->canJump && _chara->CanJump())
		|| (_chara->canAttack && (newState == static_cast<uint8>(StateType::RATTACK) || newState == static_cast<uint8>(StateType::LATTACK)));
}

uint8 IdleRunState::getState() const
{
	return static_cast<uint8>(StateType::IDLE);
}