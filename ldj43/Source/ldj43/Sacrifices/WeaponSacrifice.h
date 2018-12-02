#pragma once

#include "Sacrifice.h"

#include "UObject/NoExportTypes.h"
#include "WeaponSacrifice.generated.h"

UCLASS()
class LDJ43_API UWeaponSacrifice : public USacrifice
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sacrifice")
	FString weaponName = "Sword";

	virtual void GenerateDescriptions() override
	{
		_bonusDescription = "Gain a sword";
		_malusDescription = "Lose your sword (if you have one)";
	};

	void Regenerate() override
	{
	}
	void ApplyBonus(AMainCharacter* chara) override
	{
		chara->SetWeapon(weaponName, false);
	}
	void ApplyMalus(AMainCharacter* chara) override
	{
		chara->SetWeapon("", false);
	}
};