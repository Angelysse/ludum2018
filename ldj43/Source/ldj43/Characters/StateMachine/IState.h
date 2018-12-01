#pragma once

enum class StateType : uint8
{
	IDLE = 0,
	RATTACK,
	LATTACK,
	JUMP
};

class IState
{
protected:
	class AGlobalCharacter* _chara = nullptr;

public:
	IState(AGlobalCharacter* chara) : _chara{ chara }
	{
	}

	//Methods
	virtual void onEnterState() = 0;
	virtual void onExitState() = 0;
	virtual bool canSwitchTo(uint8 newState) const = 0;

	//Getters
	virtual uint8 getState() const = 0;
};