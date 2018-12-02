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