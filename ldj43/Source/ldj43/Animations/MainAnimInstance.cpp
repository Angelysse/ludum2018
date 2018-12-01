#include "MainAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	_charac = Cast<AMainCharacter>(TryGetPawnOwner());
}

void UMainAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!_charac)
		return;

	FVector velocity = _charac->GetVelocity();
	FRotator worldRotation = _charac->GetActorRotation();

	FVector2D movement = (FVector2D)worldRotation.UnrotateVector(velocity);

	direction = movement.GetSafeNormal();
	relativeSpeed = movement.Size() / _charac->GetMovementComponent()->GetMaxSpeed();
}