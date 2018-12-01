#pragma once

#include "GameFramework/Character.h"

#include "Game/GlobalPlayerState.h"
#include "Items/ItemComponentBase.h"
#include "Weapons/WeaponComponentBase.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "StateMachine/StateMachine.h"

#include "MainCharacter.generated.h"

UCLASS()
class LDJ43_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	private:
		UItemComponentBase*		_item = nullptr;

		UWeaponComponentBase*	_lWeapon = nullptr;
		UWeaponComponentBase*	_rWeapon = nullptr;

		bool					_isAttacking = false;

		StateMachine _sMachine = StateMachine(this);

	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USpringArmComponent* _cameraBoom = nullptr;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* _camera = nullptr;

		void BeginPlay() override;

	public:
		AMainCharacter();

		UCameraComponent const* GetCameraComponent();

		void SetMaxHP(float _maxHp);
		void SetWeapon(const FString& name, bool isRight = true);

		UFUNCTION(BlueprintCallable, Category = "Player")
		uint8 GetState() const;

		void Tick(float DeltaTime) override;

		void UseItem();

		void LAttack();
		void RAttack();

		void StartJump();
		UFUNCTION(BlueprintCallable, Category = "Player")
		void EndJump();
};