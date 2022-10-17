#include "Weapon.h"

Weapon::Weapon(float fireTimer, float interval)
{
	this->fireTimer = fireTimer;
	this->intervalWeapon = interval;
}

Weapon::~Weapon()
{
}