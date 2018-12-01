#pragma once

#include "GameFramework/PlayerState.h"
#include "GlobalPlayerState.generated.h"

UCLASS()
class LDJ43_API AGlobalPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	bool canJump = true;
};