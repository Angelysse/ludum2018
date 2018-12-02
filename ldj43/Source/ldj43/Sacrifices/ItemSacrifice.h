#pragma once

#include "Sacrifice.h"

#include "UObject/NoExportTypes.h"
#include "ItemSacrifice.generated.h"

UCLASS()
class LDJ43_API UItemSacrifice : public USacrifice
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sacrifice")
	FString itemName = "Potion";

	virtual void GenerateDescriptions() override
	{
		_bonusDescription = "Gain a health potion";
		_malusDescription = "Lose your potion (if you have one)";
	};

	void Regenerate() override
	{
	}
	void ApplyBonus(AMainCharacter* chara) override
	{
		chara->SetItem(itemName);
	}
	void ApplyMalus(AMainCharacter* chara) override
	{
		chara->SetItem("");
	}
};