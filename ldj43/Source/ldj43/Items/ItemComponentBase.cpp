#include "ItemComponentBase.h"

#include "Engine/World.h"
#include "TimerManager.h"

UItemComponentBase::UItemComponentBase()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UItemComponentBase::BeginPlay()
{
	Super::BeginPlay();
}

void UItemComponentBase::EndPlay(EEndPlayReason::Type const EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(_timerHandle);
}

void UItemComponentBase::Use()
{
	if (!_isInCooldown)
	{
		GetWorld()->GetTimerManager().SetTimer(_timerHandle, [this]()
		{
			//Cooldown finished, item usable again
			_isInCooldown = false;
		}, _cooldown, false);
	}
}