#include "MainCharacter.h"

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

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

UCameraComponent* AMainCharacter::GetCameraComponent()
{
	return _camera;
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
	if (_lWeapon && !_isAttacking)
	{
		_isAttacking = true;
		_lWeapon->Use();

		//_isAttacking = false on end animation
	}
}

void AMainCharacter::RAttack()
{
	if (_rWeapon && !_isAttacking)
	{
		_isAttacking = true;
		_rWeapon->Use();

		//_isAttacking = false on end animation
	}
}

void AMainCharacter::Jump()
{
	if (Cast<AGlobalPlayerState>(PlayerState)->canJump && CanJump())
		Super::Jump();
}

void AMainCharacter::SetupFirstPersonCamera()
{
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, -1.0f, 0.0f);

	_cameraBoom->SetRelativeLocation(FVector(0.0f, 30.0f, 130.0f));
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

	_cameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));
	_cameraBoom->TargetArmLength = 300.0f;

	_camera->bUsePawnControlRotation = true;
	
	GetMesh()->SetCastShadow(true);
	GetMesh()->UnHideBoneByName("neck_01");
}