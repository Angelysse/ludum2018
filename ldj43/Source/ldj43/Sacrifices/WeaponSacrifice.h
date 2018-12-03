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

	UWeaponSacrifice()
	{
		_image = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, TEXT("Texture2D'/Game/Resources/Textures/epeeicone.epeeicone'")));
		GenerateDescriptions();
	}

	virtual void GenerateDescriptions() override
	{
		_bonusDescription = "Gain a " + weaponName;
		_malusDescription = "Lose your " + weaponName + "(if you have one)";
	};

	void Regenerate() override
	{
	}
	void ApplyBonus(AMainCharacter* chara) override
	{
		chara->PickupWeapon(weaponName);
	}
	void ApplyMalus(AMainCharacter* chara) override
	{
		chara->PickupWeapon("");
	}
};