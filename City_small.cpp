#include "City_small.h"

int City_small::idCount = 0;

City_small::City_small()
{
	id = idCount++;
	warriors.resize(2);
}

int City_small::getOccupier()const
{
	bool bluein = warriors[0] == nullptr ? false : (warriors[0]->Action());
	bool redin = warriors[1] == nullptr ? false : (warriors[1]->Action());
	if (bluein && !redin)
		return 0;
	if (!bluein && redin)
		return 1;
	return -1;
}

bool City_small::ifHaveSeat(int campID)
{
	if (campID >= 2)
		return false;
	else if (warriors[campID] == nullptr)
		return true;
	else
		return false;
}

baseWarrior* City_small::enterWarrior(baseWarrior* war)
{
	if (war->getCamp() >= 2)
		return nullptr;
	if (warriors[war->getCamp()] == nullptr)
	{
		warriors[war->getCamp()] = war;
		war->location = this;
		return war;
	}
	return nullptr;
}

baseWarrior* City_small::exitWarrior(baseWarrior* war)
{
	if (war->getCamp() >= 2)
		return nullptr;
	if (warriors[war->getCamp()] == war)
	{
		warriors[war->getCamp()] = nullptr;
		return war;
	}
	return nullptr;
}

void City_small::OnHourEnd()
{
	Log("blue warrior:" + (warriors[0] == nullptr ? "null" : warriors[0]->name) +
		",red warrior:" + (warriors[1] == nullptr ? "null" : warriors[1]->name) +
		" ;flag:" + (campfig == -1 ? "null" : std::to_string(campfig)));
}

void City_small::Updata()
{
	if (wow::worldTime.getMin() == 20)
	{
		life += 10;
		Log("produce 10 life! now have:" + std::to_string(life));
	}
}
