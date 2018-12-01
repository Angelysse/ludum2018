#pragma once

#include "IState.h"

class StateMachine
{
	private:
		//Variables
		IState*		_currentState;

	public:
		//Constructors
		StateMachine(IState* initState);

		//Methods
		bool switchTo(IState* nextState);
};