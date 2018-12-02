#pragma once

#include "ISacrifice.h"

class SToFPSCam : public ISacrifice
{
public:
	using ISacrifice::ISacrifice;

	void Use()
	{
		_chara->SetupFirstPersonCamera();
	}
};