#include "StateMachine.h"

StateMachine::StateMachine(IState* initState):
	_currentState{initState}
{
	if (_currentState != nullptr)
	{
		_currentState->onEnterState();
	}
}

bool StateMachine::switchTo(IState* nextState)
{
	if (_currentState && nextState && _currentState->canSwitchTo(nextState->getState()))
	{
		_currentState->onExitState();
		_currentState = nextState;
		_currentState->onEnterState();

		return true;
	}

	return false;
}

//Idle -> Jump
//Jump -> Idle
//Idle -> Attack
//Attack -> Idle