// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Game/GlobalGameMode.h"
#include "AI/AIManager.h"

#include "ArenaGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LDJ43_API AArenaGameMode : public AGlobalGameMode
{
	GENERATED_BODY()

	private:
		//Variables
		AAIManager*		_aiManager = nullptr;

		//Custom Methods
		void initAIManager();

	public:
		//Overriden Methods
		virtual void InitGame(FString const& MapName, FString const& Options, FString& ErrorMessage) override;
		virtual void BeginPlay() override;
};
