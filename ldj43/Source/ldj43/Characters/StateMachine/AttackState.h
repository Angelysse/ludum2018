#pragma once

#include "IState.h"

class AttackState : public IState
{
	public:
		//Methods
		void onEnterState() override;
		void onExitState() override;
		bool canSwitchTo(uint8 newState) override;

		//Getters
		uint8 getState() const override;
};