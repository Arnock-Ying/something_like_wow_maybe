#include "nomelWarrior.h"
#include "Headquarters.h"

int nomelWarrior::defaultHealth = 20;
int nomelWarrior::defaultAttack = 9;

baseWarrior* nomelWarrior::factionWar()
{
	baseWarrior* war = new nomelWarrior();
	war->name = "nomel";
	return war;
}

int& nomelWarrior::DefaultHealth()
{
	return defaultHealth;
}

int& nomelWarrior::DefaultAttack()
{
	return defaultAttack;
}


