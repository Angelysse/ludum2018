#include "Weapon.h"

void AWeapon::SetActive(bool b)
{
	SetActorTickEnabled(b);
	SetActorHiddenInGame(!b);
}