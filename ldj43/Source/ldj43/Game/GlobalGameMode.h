#pragma once

#include "GameFramework/GameMode.h"

#include "Weapons/Weapon.h"

#include "GlobalGameMode.generated.h"

UCLASS()
class LDJ43_API AGlobalGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, AWeapon*> weapons;

	AWeapon* GetWeapon(const FString& name);
	void FreeWeapon(AWeapon* weapon);

	DECLARE_EVENT(AGlobalGameMode, GameEvents)
	GameEvents onEndGame;
};
