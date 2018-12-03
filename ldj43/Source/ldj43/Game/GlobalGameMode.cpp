#include "GlobalGameMode.h"
#include "Engine.h"

AWeapon* AGlobalGameMode::GetWeapon(const FString& name)
{
	AWeapon* weapon = weapons[name];
	weapon->SetActive(true);

	return weapon;
}

void AGlobalGameMode::FreeWeapon(AWeapon* weapon)
{
	weapon->SetActive(false);
	weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}