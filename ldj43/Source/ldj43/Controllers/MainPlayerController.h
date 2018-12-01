// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
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

		//Custom Methods
		
};
