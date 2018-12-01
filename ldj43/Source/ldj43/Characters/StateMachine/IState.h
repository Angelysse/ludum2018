#pragma once

enum class StateType : uint8
{
	IDLE = 0,
	ATTACK,
	RELOAD,
	JUMP
};

class IState
{
	public:
		//Methods
		virtual void onEnterState() = 0;
		virtual void onExitState() = 0;
		virtual bool canSwitchTo(uint8 newState) = 0;

		//Getters
		virtual uint8 getState() const = 0;
};