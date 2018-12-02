#pragma once

#include "GameFramework/Actor.h"
#include "CubeActor.generated.h"

UCLASS()
class LDJ43_API ACubeActor : public AActor
{
	GENERATED_BODY()
	
	static UMaterial* _mat;

public:	
	ACubeActor();

	void BeginPlay();
};