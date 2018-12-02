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