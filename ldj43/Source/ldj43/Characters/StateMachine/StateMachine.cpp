#include "StateMachine.h"

#include "IdleRunState.h"
#include "JumpState.h"
#include "AttackState.h"

StateMachine::StateMachine(StateType initState):
	_currentState{nullptr}
{
	initStates();
	
	_currentState = _states[static_cast<uint8>(initState)];
	_currentState->onEnterState();
}

StateMachine::~StateMachine()
{
	delete _states[0];
	delete _states[1];
	delete _states[2];
}

void StateMachine::initStates()
{
	_states[0] = new IdleRunState();
	_states[1] = new AttackState();
	_states[2] = new JumpState();
}

bool StateMachine::switchTo(StateType nextState)
{
	IState* state = _states[static_cast<uint8>(nextState)];

	if (_currentState && _currentState->canSwitchTo(state->getState()))
	{
		_currentState->onExitState();
		_currentState = state;
		_currentState->onEnterState();

		return true;
	}

	return false;
}