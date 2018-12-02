#include "MainCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Game/ArenaGameMode.h"
#include "Game/ArenaGameState.h"
#include "BasicAICharacter.h"
#include "../Animations/MainAnimInstance.h"

#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	_cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_cameraBoom->SetupAttachment((USceneComponent*)GetMesh());
	_cameraBoom->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_camera->SetupAttachment(_cameraBoom, USpringArmComponent::SocketName);

	//mesh offset
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	_cameraBoom->bUsePawnControlRotation = true;

	SetupThirdPersonCamera();
}

UCameraComponent const* AMainCharacter::GetCameraComponent()
{
	return _camera;
}

void AMainCharacter::SetItem(const FString& name)
{
	if (!name.IsEmpty())
	{

	}
}

void AMainCharacter::SetWeapon(const FString& name, bool isRight)
{
	auto gm = Cast<AGlobalGameMode>(GetWorld()->GetAuthGameMode());

	if (isRight)
	{
		if (_rWeapon)
			gm->FreeWeapon(_rWeapon);

		if(!name.IsEmpty())
			_rWeapon = gm->GetWeapon("r" + name);
	}
	else
	{
		if (_lWeapon)
			gm->FreeWeapon(_lWeapon);

		if (!name.IsEmpty())
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
	_animInstance->attackSpeed = (_lWeapon != nullptr ? _lWeapon->_attackSpeed : basicAttackSpeed) * attackSpeedMultiplier;
	_sMachine.switchTo(StateType::LATTACK);
}

void AMainCharacter::RAttack()
{
	_animInstance->attackSpeed = (_rWeapon != nullptr ? _rWeapon->_attackSpeed : basicAttackSpeed) * attackSpeedMultiplier;
	_sMachine.switchTo(StateType::RATTACK);
}

bool AMainCharacter::canHit(AGlobalCharacter const* other)
{
	return Cast<ABasicAICharacter>(other) != nullptr;
}

void AMainCharacter::StartJump()
{
	_sMachine.switchTo(StateType::JUMP);
}

void AMainCharacter::EndJump()
{
	if (_sMachine.getState() == static_cast<uint8>(StateType::JUMP))
		_sMachine.switchTo(StateType::IDLE);
}

void AMainCharacter::SetupFirstPersonCamera()
{
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, -1.0f, 0.0f);

	_cameraBoom->SetRelativeLocation(FVector(0.0f, 10.0f, 150.0f));
	_cameraBoom->TargetArmLength = 0.0f;

	_camera->bUsePawnControlRotation = false;

	GetMesh()->SetCastShadow(false);
	GetMesh()->HideBoneByName("neck_01", EPhysBodyOp::PBO_None);
}

void AMainCharacter::SetupThirdPersonCamera()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

	_cameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	_cameraBoom->TargetArmLength = 300.0f;

	_camera->bUsePawnControlRotation = true;
	
	GetMesh()->SetCastShadow(true);
	GetMesh()->UnHideBoneByName("neck_01");
}

float AMainCharacter::getAttackPower(bool isRightSlot) const
{
	if (isRightSlot)
	{
		if (_rWeapon != nullptr)
		{
			return _rWeapon->_damages;
		}
	}
	else if (_lWeapon != nullptr)
	{
		return _lWeapon->_damages;
	}

	return AGlobalCharacter::getAttackPower(isRightSlot);
}

void AMainCharacter::onTakeDamageFrom(AGlobalCharacter* other)
{
	//Nothing to do
}

void AMainCharacter::onDie(AGlobalCharacter* deadChar, AGlobalCharacter* killedBy)
{
	AGlobalCharacter::onDie(deadChar, killedBy);

	if (deadChar == this)
	{
		AArenaGameState* gameState = GetWorld()->GetGameState<AArenaGameState>();
		if (gameState != nullptr)
		{
			gameState->switchToEndGame();
		}
	}
}