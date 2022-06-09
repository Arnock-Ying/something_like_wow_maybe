#pragma once
#include "baseWarrior.h"

class wolf :
    public baseWarrior
{
private:
	static int defaultHealth;
	static int defaultAttack;
	bool ifWin = false;
public:
	wolf();
	baseWarrior* factionWar();
	int& DefaultAttack() { return defaultAttack; }
	int& DefaultHealth() { return defaultHealth; }

	void OnAfterAttack();
};

