#pragma once

#include "Components/StaticMeshComponent.h"
#include "WeaponComponentBase.generated.h"

UCLASS(Blueprintable)
class LDJ43_API UWeaponComponentBase : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:

public:
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float _attackSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float _damages = 10.0f;

	//Methods
	virtual void Use() {};
};