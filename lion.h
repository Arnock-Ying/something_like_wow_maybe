#pragma once
#include "baseWarrior.h"

class lion :
	public baseWarrior
{
private:
	static int defaultHealth;
	static int defaultAttack;
	static int K;
	int loyalty;
	int late_health;
	bool ifTTK = false;
	bool ifWin = false;
public:
	lion();
	baseWarrior* factionWar();
	int& DefaultAttack() { return defaultAttack; }
	int& DefaultHealth() { return defaultHealth; }

	void Start();
	void OnAttack(baseWarrior*);
	void OnHourEnd();
	void OnWin();
	void OnAfterAttack();
	void UpdataStart();
	void OnDead(baseWarrior*);
	inline void setK(int x) { K = x; }
	inline int getK() { return K; }
};

