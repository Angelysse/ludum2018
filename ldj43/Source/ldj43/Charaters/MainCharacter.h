#pragma once

#include "GameFramework/Character.h"

#include "Items/ItemComponentBase.h"
#include "Weapons/WeaponComponentBase.h"

#include "MainCharacter.generated.h"

UCLASS()
class LDJ43_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	float _hp = 100.0f;
	float _speed = 10.0f;

	UItemComponentBase* _item = nullptr;

	UWeaponComponentBase* _lWeapon = nullptr;
	UWeaponComponentBase* _rWeapon = nullptr;

protected:
	void BeginPlay() override;

public:
	AMainCharacter();

	void Tick(float DeltaTime) override;

	void UseItem();

	void LAttack();
	void RAttack();
};