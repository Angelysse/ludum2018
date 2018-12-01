#pragma once

#include "Components/StaticMeshComponent.h"
#include "WeaponComponentBase.generated.h"

UCLASS()
class LDJ43_API UWeaponComponentBase : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:
	float _attackSpeed = 1.0f;
	float _damages = 10.0f;

public:
	virtual void Use() = 0;
};