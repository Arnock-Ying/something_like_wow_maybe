#include "iceman.h"
int iceman::defaultHealth = 20;
int iceman::defaultAttack = 2;
iceman::iceman() {
	int step = 0;
}

baseWarrior* iceman::factionWar()
{
	baseWarrior* war = new iceman();
	war->name = "iceman";
	return war;
}

void iceman::onMovde()
{
	++step;
	if (step == 2) {
		step = 0;
		if (health > 9) health -= 9;
		else health = 1;
		power += 20;
	}
}
