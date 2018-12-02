#include "GlobalGameMode.h"

AWeapon* AGlobalGameMode::GetWeapon(const FString& name)
{
	AWeapon* weapon = weapons[name];
	weapon->GetRootComponent()->SetActive(true);

	return weapon;
}

void AGlobalGameMode::FreeWeapon(AWeapon* weapon)
{
	weapon->GetRootComponent()->SetActive(false);
	weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}