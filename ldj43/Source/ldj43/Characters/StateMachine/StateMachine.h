#pragma once

#include "IdleRunState.h"
#include "LAttackState.h"
#include "RAttackState.h"
#include "JumpState.h"
#include "DeathState.h"

class StateMachine
{
	private:
		//Variables
		IState*		_currentState;
		IState*		_states[6];

		//Methods
		void initStates(AGlobalCharacter* chara);

	public:
		//Constructors
		StateMachine(AGlobalCharacter* chara, StateType initState = StateType::IDLE);

		//Destructor
		~StateMachine();

		//Methods
		bool switchTo(StateType nextState);

		uint8 getState() const;
};