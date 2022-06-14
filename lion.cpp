#include "lion.h"
#include "basePlace.h"
#include "GameManager.h"
int lion::defaultHealth = 6;
int lion::defaultAttack = 7;
int lion::K = 1;
lion::lion()
{
	int loyalty = 1;
	int late_health = 0;
}
baseWarrior* lion::factionWar()
{
	baseWarrior* war = new lion();
	war->name = "lion";
	return war;
}

void lion::Start()
{
	loyalty = location->getLive();
	drawPut("Its loyalty is " + std::to_string(loyalty));
}

void lion::OnAttack(baseWarrior*)
{
	ifTTK = true;
}

void lion::OnHourEnd()
{
	ifTTK = false;
	ifWin = false;
}

void lion::OnWin()
{
	ifWin = true;
}

void lion::OnAfterAttack()
{
	if (!ifWin && ifTTK)
	{
		loyalty -= K;
	}
}

void lion::UpdataStart()
{
	if (wow::worldTime == 5)
	{
		if (loyalty <= 0 && location != dynamic_cast<basePlace*>(GameManager::manager->Header(destID)))
		{
			drawPut(name + " run array!进行一个飞快的润！");
			Destroy();
		}
	}
	if (wow::worldTime == 40)
	{
		late_health = health;
	}
}

void lion::OnDead(baseWarrior* killer)
{
	killer->setHealth(killer->getHealth() + late_health);
}

