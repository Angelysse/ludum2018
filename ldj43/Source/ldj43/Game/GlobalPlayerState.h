#pragma once

#include "GameFramework/PlayerState.h"
#include "GlobalPlayerState.generated.h"

UCLASS()
class LDJ43_API AGlobalPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float maxHp = 100.0f;
	float hp = maxHp;

	bool canJump = true;
};