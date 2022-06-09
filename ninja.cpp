#include "ninja.h"
int ninja::defaultHealth = 6;
int ninja::defaultAttack = 4;

ninja::ninja() {
	maxArmsNum = 2;
	ifCounterattack = false;
}

baseWarrior* ninja::factionWar()
{
	baseWarrior* war = new ninja();
	war->name = "ninja";
	return war;
}

void ninja::OnAttack(baseWarrior*)
{
	ifTTK = true;
}

void ninja::OnHourEnd()
{
	ifTTK = false;
}
