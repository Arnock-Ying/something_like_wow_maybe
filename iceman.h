#pragma once
#include "baseWarrior.h"

class iceman :
	public baseWarrior
{
private:
	static int defaultHealth;
	static int defaultAttack;
	int step;
public:
	iceman();
	baseWarrior* factionWar();
	int& DefaultAttack() { return defaultAttack; }
	int& DefaultHealth() { return defaultHealth; }

	void onMovde();
};

