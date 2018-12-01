#include "MainCharacter.h"


AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMainCharacter::SetMaxHP(float _maxHp)
{
	auto pState = Cast<AGlobalPlayerState>(PlayerState);

	pState->maxHp = _maxHp;

	if (pState->hp > pState->maxHp)
		pState->hp = pState->maxHp;
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCharacter::UseItem()
{
	if (_item)
		_item->Use();
}

void AMainCharacter::LAttack()
{
	if (_lWeapon)
		_lWeapon->Use();
}

void AMainCharacter::RAttack()
{
	if (_rWeapon)
		_rWeapon->Use();
}

void AMainCharacter::Jump()
{
	if (Cast<AGlobalPlayerState>(PlayerState)->canJump && CanJump())
		Super::Jump();
}