#include "GlobalGameMode.h"

UWeaponComponentBase* AGlobalGameMode::GetWeapon(const FString& name)
{
	UWeaponComponentBase* weapon = weapons[name];
	weapon->SetActive(true);

	return weapon;
}

void AGlobalGameMode::FreeWeapon(UWeaponComponentBase* weapon)
{
	weapon->SetActive(false);
	weapon->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}