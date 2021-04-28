#pragma once

enum enum_DamageType
{
	FIRE,
	ICE,
	VOID,
	PENIS
};

class person
{
private:
	int health;
public:
	person(int currentHealth) : health{ currentHealth } {};

	void calculateCurrentHealth(int damage, enum_DamageType damageType, int damagingPlayer_ID);

	int getHealth();
};

