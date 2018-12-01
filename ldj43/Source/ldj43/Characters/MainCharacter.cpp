#include "MainCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Game/ArenaGameMode.h"

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

UCameraComponent const* AMainCharacter::GetCameraComponent()
{
	return _camera;
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

void AMainCharacter::Jump()
{
	if (Cast<AGlobalPlayerState>(PlayerState)->canJump && CanJump())
		Super::Jump();
}