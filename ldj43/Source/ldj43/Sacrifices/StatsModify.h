#pragma once

#include "Sacrifice.h"

#include "UObject/NoExportTypes.h"
#include "StatsModify.generated.h"

UCLASS()
class LDJ43_API UStatsModify : public USacrifice
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sacrifices")
	float _minHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sacrifices")
	float _maxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sacrifices")
	float _minAS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sacrifices")
	float _maxAS;

	float currHp = 0.0f;
	float currAS = 0.0f;

	void Regenerate() override
	{
		currHp = FMath::FRandRange(_minHP, _maxHP);
		currAS = FMath::FRandRange(_minAS, _maxAS);
	}
	void ApplyBonus(AMainCharacter* chara) override
	{
		chara->SetMaxHP(chara->GetMaxHP() + currHp);
		chara->attackSpeedMultiplier += currAS;
	}
	void ApplyMalus(AMainCharacter* chara) override
	{
		chara->SetMaxHP(chara->GetMaxHP() - currHp);
		chara->attackSpeedMultiplier -= currAS;
	}
};