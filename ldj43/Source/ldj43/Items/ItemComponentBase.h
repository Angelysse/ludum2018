#pragma once

#include "Components/ActorComponent.h"
#include "ItemComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LDJ43_API UItemComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	UItemComponentBase();

	virtual void Use() = 0;
};