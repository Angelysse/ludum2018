#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class LDJ43_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float _attackSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float _damages = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FTransform lTr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FTransform rTr;

	void SetActive(bool b);
	void ResetTransform(bool isRight)
	{
		RootComponent->SetWorldTransform(isRight ? rTr : lTr);
	}
};
