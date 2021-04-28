#include "person.h"

void person::calculateCurrentHealth(int damage, enum_DamageType damageType, int damagingPlayer_ID)
{
	switch (damageType)
	{
	case FIRE:
		damage *= 0.5;
		break;
	case ICE:
		damage *= 1.4;
		break;
	case VOID:
		damage *= 2;
		break;
	case PENIS:
		damage *= 1000000;
		break;
	}

	health -= damage;
}

int person::getHealth()
{
	return health;
}
