#pragma once

#include "GameFramework/Character.h"

#include "Game/GlobalPlayerState.h"

#include "Items/ItemComponentBase.h"
#include "Weapons/WeaponComponentBase.h"

#include "MainCharacter.generated.h"

UCLASS()
class LDJ43_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	UItemComponentBase* _item = nullptr;

	UWeaponComponentBase* _lWeapon = nullptr;
	UWeaponComponentBase* _rWeapon = nullptr;

protected:
	void BeginPlay() override;

public:
	AMainCharacter();

	void SetMaxHP(float _maxHp);

	void Tick(float DeltaTime) override;

	void UseItem();

	void LAttack();
	void RAttack();

	void Jump() override;
};