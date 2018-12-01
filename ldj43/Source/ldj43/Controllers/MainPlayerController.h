// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */

enum class Action : uint8
{
	JUMP = 0,
	LEFT_ATTACK,
	RIGHT_ATTACK,
	USE_ITEM,
	LEFT_SACRIFICE,
	RIGHT_SACRIFICE
};

UCLASS()
class LDJ43_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

	private:
		//Variables

		//Custom Methods
		void moveForward(float value);
		void moveRight(float value);
		void rotateCameraYaw(float value);
		void rotateCameraPitch(float value);
		void jump();
		void useLeftWeaponSlot();
		void useRightWeaponSlot();
		void useItem();
		void choseLeftSacrifice();
		void choseRightSacrifice();

		void setupMovementInputs();
		void setupBasicInputs();

	public:
		//Overriden Methods
		void Possess(APawn* possessedPawn) override;
		void SetupInputComponent() override;

		void enableAction(Action action);
		void disableAction(Action action);
		void modifyAction(Action action, bool shouldEnable);
};