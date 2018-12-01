#pragma once

#include "GameFramework/Character.h"

#include "Game/GlobalPlayerState.h"
#include "Items/ItemComponentBase.h"
#include "Weapons/WeaponComponentBase.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "MainCharacter.generated.h"

UCLASS()
class LDJ43_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	UItemComponentBase* _item = nullptr;

	UWeaponComponentBase* _lWeapon = nullptr;
	UWeaponComponentBase* _rWeapon = nullptr;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* _cameraBoom = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* _camera = nullptr;

	void BeginPlay() override;

public:
	AMainCharacter();

	UCameraComponent* GetCameraComponent();

	void SetMaxHP(float _maxHp);

	void Tick(float DeltaTime) override;

	void UseItem();

	void LAttack();
	void RAttack();

	void Jump() override;
};