#pragma once

#include "Sacrifices/Bonus.h"
#include "Sacrifices/Malus.h"
#include "Engine/Texture2D.h"

#include "UObject/NoExportTypes.h"
#include "Sacrifice.generated.h"

UCLASS(Blueprintable)
class LDJ43_API USacrifice : public UObject, public IBonus, public IMalus
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString _bonusDescription = "unspecified";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString _malusDescription = "unspecified";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTexture2D* _image;

public:
	USacrifice() 
	{
		GenerateDescriptions(); 
	};

	virtual void GenerateDescriptions() {};
	void Regenerate() override {}

	UFUNCTION(BlueprintCallable)
	void ApplyBonus(AMainCharacter* chara) override {}
	UFUNCTION(BlueprintCallable)
	void ApplyMalus(AMainCharacter* chara) override {}
};