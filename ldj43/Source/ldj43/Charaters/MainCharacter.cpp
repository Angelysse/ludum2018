#include "MainCharacter.h"


AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
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