#include "Sword.h"
#include "faction.h"


baseArms* Sword::FactionArm()
{
	baseArms* sw = new Sword;
	sw->name = "Sword";
	return sw;
}

bool Sword::ifDestroy()
{
	return power == 0;
}

void Sword::OnUsing(baseWarrior*)
{
	power = power * 0.8;
}
