#include "MainAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	_chara = Cast<AMainCharacter>(TryGetPawnOwner());
}

void UMainAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!_chara)
		return;

	FVector velocity = _chara->GetVelocity();
	FRotator worldRotation = _chara->GetActorRotation();

	FVector2D movement = (FVector2D)worldRotation.UnrotateVector(velocity);

	direction = movement.GetSafeNormal();
	relativeSpeed = movement.Size() / _chara->GetMovementComponent()->GetMaxSpeed();
}