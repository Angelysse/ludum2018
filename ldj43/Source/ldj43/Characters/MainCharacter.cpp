#include "MainCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Game/ArenaGameMode.h"

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
void AMainCharacter::SetWeapon(const FString& name, bool isRight)
{
	auto gm = Cast<AGlobalGameMode>(GetWorld()->GetAuthGameMode());

	if (isRight)
	{
		if (_rWeapon)
			gm->FreeWeapon(_rWeapon);

		_rWeapon = gm->GetWeapon("r" + name);
	}
	else
	{
		if (_lWeapon)
			gm->FreeWeapon(_lWeapon);

		_lWeapon = gm->GetWeapon("l" + name);
	}
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