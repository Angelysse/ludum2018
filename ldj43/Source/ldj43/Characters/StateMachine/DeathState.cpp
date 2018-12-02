#include "DeathState.h"
#include "Characters/MainCharacter.h"
#include "Components/CapsuleComponent.h"

void DeathState::onEnterState()
{
	_chara->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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