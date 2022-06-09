#pragma once
#include "baseWarrior.h"

class dragon :
	public baseWarrior
{
private:
	static int defaultHealth;
	static int defaultAttack;
	double morale;
	bool ifTTK = false;
	bool ifWin = false;
public:
	baseWarrior* factionWar();
	int& DefaultAttack() { return defaultAttack; }
	int& DefaultHealth() { return defaultHealth; }


	void Start();
	void OnAttack(baseWarrior*);
	void OnHourEnd();
	void OnWin();
	void OnAfterAttack();
};

