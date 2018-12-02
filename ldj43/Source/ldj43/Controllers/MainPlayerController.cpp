// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"

#include "Engine.h"
#include "EngineGlobals.h"
#include "GameFramework/Pawn.h"

#include "Characters/MainCharacter.h"

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
	
	//Enable all actions
	enableAction(Action::JUMP);
	enableAction(Action::LEFT_ATTACK);
	enableAction(Action::RIGHT_ATTACK);
	enableAction(Action::USE_ITEM);
	enableAction(Action::LEFT_SACRIFICE);
	enableAction(Action::RIGHT_SACRIFICE);
}

void AMainPlayerController::moveForward(float value)
{
	AMainCharacter* controlledCharacter = Cast<AMainCharacter>(GetPawn());

	if (controlledCharacter != nullptr && controlledCharacter->GetState() != static_cast<uint8>(StateType::DEATH))
		controlledCharacter->AddMovementInput(controlledCharacter->GetCameraComponent()->GetForwardVector(), value);
}

void AMainPlayerController::moveRight(float value)
{
	AMainCharacter* controlledCharacter = Cast<AMainCharacter>(GetPawn());

	if (controlledCharacter != nullptr && controlledCharacter->GetState() != static_cast<uint8>(StateType::DEATH))
		controlledCharacter->AddMovementInput(controlledCharacter->GetCameraComponent()->GetRightVector(), value);
}

void AMainPlayerController::rotateCameraYaw(float value)
{
	APawn* controlledCharacter = GetPawn();

	if (controlledCharacter != nullptr)
		controlledCharacter->AddControllerYawInput(value);
}

void AMainPlayerController::rotateCameraPitch(float value)
{
	APawn* controlledCharacter = GetPawn();

	if (controlledCharacter != nullptr)
		controlledCharacter->AddControllerPitchInput(value);
}

void AMainPlayerController::jump()
{
	AMainCharacter* controlledCharacter = Cast<AMainCharacter>(GetPawn());

	if (controlledCharacter != nullptr && controlledCharacter->GetState() != static_cast<uint8>(StateType::DEATH))
		controlledCharacter->StartJump();
}

void AMainPlayerController::useLeftWeaponSlot()
{
	AMainCharacter* controlledCharacter = Cast<AMainCharacter>(GetPawn());

	if (controlledCharacter != nullptr && controlledCharacter->GetState() != static_cast<uint8>(StateType::DEATH))
		controlledCharacter->LAttack();

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("AMainPlayerController::useLeftWeaponSlot()"));
}

void AMainPlayerController::useRightWeaponSlot()
{
	AMainCharacter* controlledCharacter = Cast<AMainCharacter>(GetPawn());

	if (controlledCharacter != nullptr && controlledCharacter->GetState() != static_cast<uint8>(StateType::DEATH))
		controlledCharacter->RAttack();

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("AMainPlayerController::useRightWeaponSlot()"));
}

void AMainPlayerController::useItem()
{
	AMainCharacter* controlledCharacter = Cast<AMainCharacter>(GetPawn());

	if (controlledCharacter != nullptr && controlledCharacter->GetState() != static_cast<uint8>(StateType::DEATH))
		controlledCharacter->UseItem();

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("AMainPlayerController::useItem()"));
}

void AMainPlayerController::choseLeftSacrifice()
{
	//TODO

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("AMainPlayerController::choseLeftSacrifice()"));
}

void AMainPlayerController::choseRightSacrifice()
{
	//TODO

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Emerald, TEXT("AMainPlayerController::choseRightSacrifice()"));
}

void AMainPlayerController::enableAction(Action action)
{
	switch (action)
	{
		case Action::JUMP:
			InputComponent->BindAction("Jump", IE_Pressed, this, &AMainPlayerController::jump);
			break;

		case Action::LEFT_ATTACK:
			InputComponent->BindAction("LeftWeapon", IE_Pressed, this, &AMainPlayerController::useLeftWeaponSlot);
			break;

		case Action::RIGHT_ATTACK:
			InputComponent->BindAction("RightWeapon", IE_Pressed, this, &AMainPlayerController::useRightWeaponSlot);
			break;

		case Action::USE_ITEM:
			InputComponent->BindAction("Item", IE_Pressed, this, &AMainPlayerController::useItem);
			break;

		case Action::LEFT_SACRIFICE:
			InputComponent->BindAction("LeftSacrifice", IE_Pressed, this, &AMainPlayerController::choseLeftSacrifice);
			break;

		case Action::RIGHT_SACRIFICE:
			InputComponent->BindAction("RightSacrifice", IE_Pressed, this, &AMainPlayerController::choseRightSacrifice);
			break;

		default:
			//Should never pass here
			break;
	}
}

void AMainPlayerController::disableAction(Action action)
{
	InputComponent->RemoveActionBinding(static_cast<int32>(action));
}

void AMainPlayerController::modifyAction(Action action, bool shouldEnable)
{
	//Bind
	if (shouldEnable)
		enableAction(action);
	else	//Unbind
		disableAction(action);
}

#pragma endregion