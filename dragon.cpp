#include "dragon.h"
#include "basePlace.h"
int dragon::defaultHealth = 10;
int dragon::defaultAttack = 5;


baseWarrior* dragon::factionWar()
{
	baseWarrior* war = new dragon();
	war->name = "dragon";
	return war;
}

void dragon::Start()
{
	int headerLife = location->getLive();
	morale = headerLife * 1.0 / defaultHealth;
	drawPut("Its loyalty is " + std::to_string(morale));
}

void dragon::OnAttack(baseWarrior*)
{
	ifTTK = true;
}

void dragon::OnHourEnd()
{
	ifTTK = false;
	ifWin = false;
}

void dragon::OnWin()
{
	ifWin = true;
}

void dragon::OnAfterAttack()
{
	if (ifWin) morale += 0.2;
	else morale -= 0.2;
	if (ifTTK && Action() && morale > 0.8)
	{
		wow::output << "ruaaaa¡ª¡ª¡ª¡ª¡ª¡ª!\n";
		location->drawText << "ºß£¬ºß°¡°¡°¡°¡¡ª¡ª!\n";
	}
}
