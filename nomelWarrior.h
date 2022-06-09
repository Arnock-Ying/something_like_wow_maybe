#pragma once
#include "baseWarrior.h"
class nomelWarrior :
	public baseWarrior
{
private:
	static int defaultHealth;
	static int defaultAttack;
public:
	baseWarrior* factionWar();
	int& DefaultHealth();
	int& DefaultAttack();
public:
	nomelWarrior() = default;
};

