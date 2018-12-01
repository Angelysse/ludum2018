#pragma once

#include "Characters/GlobalCharacter.h"

#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

UCLASS()
class LDJ43_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	AGlobalCharacter* _chara = nullptr;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	FVector2D direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float relativeSpeed = 0u;

	void NativeInitializeAnimation() override;

	void NativeUpdateAnimation(float DeltaSeconds) override;
};