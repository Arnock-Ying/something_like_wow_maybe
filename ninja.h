#pragma once
#include "baseWarrior.h"

class ninja :
	public baseWarrior
{
private:
	static int defaultHealth;
	static int defaultAttack;
	bool ifTTK = false;
public:
	ninja();
	baseWarrior* factionWar();
	int& DefaultAttack() { return defaultAttack; }
	int& DefaultHealth() { return defaultHealth; }

	void OnAttack(baseWarrior*);
	void OnHourEnd();
};

