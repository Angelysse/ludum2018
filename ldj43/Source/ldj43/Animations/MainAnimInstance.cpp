#include "MainAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	_chara = Cast<AGlobalCharacter>(TryGetPawnOwner());
	
	if (_chara)
	{
		_chara->_animInstance = this;
	}
}

void UMainAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!_chara)
		return;

	FVector velocity = _chara->GetVelocity();
	FRotator worldRotation = _chara->GetActorRotation();

	direction = (FVector2D)worldRotation.UnrotateVector(velocity);

	relativeSpeed = direction.Size() / _chara->GetMovementComponent()->GetMaxSpeed();
}