#pragma once

#include "Sound/SoundCue.h"

#include "Components/ActorComponent.h"
#include "ItemComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LDJ43_API UItemComponentBase : public UActorComponent
{
	GENERATED_BODY()

	protected:
		//Variables
		FTimerHandle	_timerHandle;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundCue* useSound;

		float			_cooldown		= 0.0f;
		bool			_isInCooldown	= false;

		//Overriden Methods
		virtual void BeginPlay() override;
		virtual void EndPlay(EEndPlayReason::Type const EndPlayReason) override;

	public:
		//Constructors
		UItemComponentBase();

		//Custom Methods
		virtual void Use();
};