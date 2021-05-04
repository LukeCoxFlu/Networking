#pragma once
#include <string>
#include <mutex>

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
	std::string playerName;
	int health;
	int defence;

	std::mutex lock;
public:
	person(std::string Name, int currentHealth, int defenceFactor) : health{ currentHealth }, playerName{ Name }, defence{defenceFactor} {};

	//void calculateCurrentHealth(int damage, enum_DamageType damageType, int damagingPlayer_ID);

	void initCombat(person& enemy);

	int getHealth();
};

