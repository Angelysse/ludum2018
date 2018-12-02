#pragma once

#include "GameFramework/GameMode.h"

#include "Weapons/WeaponComponentBase.h"

#include "GlobalGameMode.generated.h"

UCLASS()
class LDJ43_API AGlobalGameMode : public AGameMode
{
	GENERATED_BODY()
	TMap<FString, UWeaponComponentBase*> weapons;
	
public:

	UWeaponComponentBase* GetWeapon(const FString& name);
	void FreeWeapon(UWeaponComponentBase* weapon);

	DECLARE_EVENT(AGlobalGameMode, GameEvents)
	GameEvents onEndGame;
};
