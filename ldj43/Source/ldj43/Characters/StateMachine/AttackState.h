#pragma once

#include "IState.h"

class AttackState : public IState
{
	public:
		using IState::IState;
		
		//Methods
		void onEnterState() override;
		void onExitState() override;
		bool canSwitchTo(uint8 newState) const override;

		//Getters
		uint8 getState() const override;
};