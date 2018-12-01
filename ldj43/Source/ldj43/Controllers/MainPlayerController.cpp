// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"

#include "GameFramework/Pawn.h"

#pragma region Overriden Methods

void AMainPlayerController::Possess(APawn* possessedPawn)
{
	Super::Possess(possessedPawn);

	//TODO
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	setupBasicInputs();
}

#pragma endregion

#pragma region Custom Methods

void AMainPlayerController::setupMovementInputs()
{
	//Axis
	InputComponent->BindAxis("MoveForward", this, &AMainPlayerController::moveForward);
	InputComponent->BindAxis("MoveRight", this, &AMainPlayerController::moveRight);
	InputComponent->BindAxis("RotateCameraYaw", this, &AMainPlayerController::rotateCameraYaw);
	InputComponent->BindAxis("RotateCameraPitch", this, &AMainPlayerController::rotateCameraPitch);
}

void AMainPlayerController::setupBasicInputs()
{
	setupMovementInputs();
	
	//TODO Bind actions
}

void AMainPlayerController::moveForward(float value)
{
	APawn* controlledPawn = GetPawn();

	if (controlledPawn != nullptr)
	{
		controlledPawn->AddMovementInput(controlledPawn->GetActorForwardVector(), value);
	}
}

void AMainPlayerController::moveRight(float value)
{
	APawn* controlledPawn = GetPawn();

	if (controlledPawn != nullptr)
	{
		controlledPawn->AddMovementInput(controlledPawn->GetActorRightVector(), value);
	}
}

void AMainPlayerController::rotateCameraYaw(float value)
{
	APawn* controlledPawn = GetPawn();

	if (controlledPawn != nullptr)
	{
		controlledPawn->AddControllerYawInput(value);
	}
}

void AMainPlayerController::rotateCameraPitch(float value)
{
	APawn* controlledPawn = GetPawn();

	if (controlledPawn != nullptr)
	{
		controlledPawn->AddControllerPitchInput(value);
	}
}

void AMainPlayerController::jump()
{
	//TODO
}

void AMainPlayerController::useLeftWeaponSlot()
{
	//TODO
}

void AMainPlayerController::useRightWeaponSlot()
{
	//TODO
}

void AMainPlayerController::useItem()
{
	//TODO
}

void AMainPlayerController::choseLeftSacrifice()
{
	//TODO
}

void AMainPlayerController::choseRightSacrifice()
{
	//TODO
}

#pragma endregion