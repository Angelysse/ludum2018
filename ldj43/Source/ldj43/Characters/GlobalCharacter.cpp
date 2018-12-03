#include "GlobalCharacter.h"
#include "../Animations/MainAnimInstance.h"
#include "../Game/ArenaGameState.h"

#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

AGlobalCharacter::AGlobalCharacter():
	_sMachine { this }
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGlobalCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	_sMachine.switchTo(StateType::IDLE);
	setupStats();
	registerToGameEvents();

	GetMesh()->SetVectorParameterValueOnMaterials("BodyColor", color);
}

// Called every frame
void AGlobalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGlobalCharacter::registerToGameEvents()
{
	AArenaGameState* gameState = GetWorld()->GetGameState<AArenaGameState>();

	if (gameState != nullptr)
	{
		//Take damage
		gameState->getOnTakeDamage().AddUFunction(this, "onTakeDamageFrom");

		//Die
		gameState->getOnDie().AddUFunction(this, "onDie");
	}
}

void AGlobalCharacter::setupStats()
{
	hp = maxHp;
}

void AGlobalCharacter::LAttack()
{
	_animInstance->attackSpeed = basicAttackSpeed * attackSpeedMultiplier;
	_sMachine.switchTo(StateType::LATTACK);
}

void AGlobalCharacter::RAttack()
{
	_animInstance->attackSpeed = basicAttackSpeed * attackSpeedMultiplier;
	_sMachine.switchTo(StateType::RATTACK);
}

bool AGlobalCharacter::canHit(AGlobalCharacter const* other)
{
	//Can't hit by default
	return false;
}

void AGlobalCharacter::takeDamageFrom(AGlobalCharacter* other, float damages)
{
	AArenaGameState* gameState = GetWorld()->GetGameState<AArenaGameState>();

	//Check still alive
	if (gameState != nullptr && hp > 0)
	{
		hp -= damages;

		gameState->onTakeDamage(other);

		//Check if die
		if (hp <= 0)
		{
			gameState->onDie(this, other);

			if (deathSound)
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), deathSound, GetTransform().GetLocation());
		}
		
		if (hitSound)
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), hitSound, GetTransform().GetLocation());
	}
}

void AGlobalCharacter::onTakeDamageFrom(AGlobalCharacter* other)
{
	//Default behavior does nothing special
}

void AGlobalCharacter::onDie(AGlobalCharacter* deadChar, AGlobalCharacter* other)
{
	if(deadChar == this)
		deadChar->_sMachine.switchTo(StateType::DEATH);
}

void AGlobalCharacter::startAttack()
{
	//Default behavior does nothing special
}

void AGlobalCharacter::endAttack()
{
	//Default behavior does nothing special
}

void AGlobalCharacter::endAttackCooldown()
{
	canAttack = true;
}

uint8 AGlobalCharacter::GetState() const
{
	return _sMachine.getState();
}

float AGlobalCharacter::getAttackPower(bool isRightSlot) const
{
	return basicAttackPower;
}

void AGlobalCharacter::SetState(uint8 state)
{
	_sMachine.switchTo(static_cast<StateType>(state));
}

float AGlobalCharacter::GetMaxHP() const
{
	return maxHp;
}
void AGlobalCharacter::SetMaxHP(float _maxHp)
{
	maxHp = _maxHp;

	if (hp > maxHp)
		hp = maxHp;
}