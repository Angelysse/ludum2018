#pragma once

#include "IState.h"

class StateMachine
{
	private:
		//Variables
		IState*		_currentState;
		IState*		_states[4];

		//Methods
		void initStates();

	public:
		//Constructors
		StateMachine(StateType initState);

		//Destructor
		~StateMachine();

		//Methods
		bool switchTo(StateType nextState);
};