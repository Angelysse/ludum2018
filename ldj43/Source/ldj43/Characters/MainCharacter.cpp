#include "MainCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	_cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_cameraBoom->SetupAttachment((USceneComponent*)GetMesh());
	_cameraBoom->SetRelativeLocation(FVector(0.0f, 0.0f, 160.0f));
	_cameraBoom->TargetArmLength = 300.0f;
	_cameraBoom->bUsePawnControlRotation = true;

	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_camera->SetupAttachment(_cameraBoom, USpringArmComponent::SocketName);
	_camera->bUsePawnControlRotation = false;
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