#include "nomelWarrior.h"
#include "Headquarters.h"

int nomelWarrior::defaultHealth = 114;
int nomelWarrior::defaultAttack = 514;

baseWarrior* nomelWarrior::factionWar()
{
	baseWarrior* war = new nomelWarrior();
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


