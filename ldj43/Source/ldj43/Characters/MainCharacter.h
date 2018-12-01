#pragma once

#include "GameFramework/Character.h"

#include "GlobalCharacter.h"
#include "Game/GlobalPlayerState.h"
#include "Items/ItemComponentBase.h"
#include "Weapons/WeaponComponentBase.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "StateMachine/StateMachine.h"

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

		StateMachine	_sMachine = StateMachine(this);					//Switch to GlobalChar

		void BeginPlay() override;

	public:
		AMainCharacter();

		UCameraComponent const* GetCameraComponent();

		void SetWeapon(const FString& name, bool isRight = true);

		UFUNCTION(BlueprintCallable, Category = "Player")				//Switch to GlobalChar
		uint8 GetState() const;											//Switch to GlobalChar

		void Tick(float DeltaTime) override;

		void UseItem();

		void StartJump();
		UFUNCTION(BlueprintCallable, Category = "Player")
		void EndJump();
};