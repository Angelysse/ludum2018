#pragma once

#include "GameFramework/Character.h"

#include "GlobalCharacter.h"
#include "Game/GlobalPlayerState.h"
#include "Items/ItemComponentBase.h"
#include "Weapons/WeaponComponentBase.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "MainCharacter.generated.h"

UCLASS()
class LDJ43_API AMainCharacter : public AGlobalCharacter
{
	GENERATED_BODY()

	private:
		UItemComponentBase*		_item = nullptr;

		UWeaponComponentBase*	_lWeapon = nullptr;
		UWeaponComponentBase*	_rWeapon = nullptr;

	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USpringArmComponent* _cameraBoom = nullptr;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UCameraComponent* _camera = nullptr;

	public:
		AMainCharacter();

		UCameraComponent const* GetCameraComponent();

		void SetWeapon(const FString& name, bool isRight = true);

		void Tick(float DeltaTime) override;

		virtual bool canHit(AGlobalCharacter const* other) override;

		void UseItem();

		void StartJump();

		UFUNCTION(BlueprintCallable, Category = "Player")
		void EndJump();

		UFUNCTION(BlueprintCallable)
		void SetupThirdPersonCamera();

		UFUNCTION(BlueprintCallable)
		void SetupFirstPersonCamera();

		virtual float getAttackPower(bool isRightSlot) const override;

		virtual void onTakeDamageFrom(AGlobalCharacter const* other) override;

		virtual void onDie(AGlobalCharacter const* killedBy) override;
};