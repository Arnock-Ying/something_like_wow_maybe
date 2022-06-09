#include "wolf.h"
#include "basePlace.h"
int wolf::defaultHealth = 5;
int wolf::defaultAttack = 5;
wolf::wolf() {
	maxArmsNum = 0;
}

baseWarrior* wolf::factionWar()
{
	baseWarrior* war = new wolf();
	war->name = "wolf";
	return war;
}

void wolf::OnAfterAttack()
{
	if (!maxArmsNum) maxArmsNum = 1;
	for (auto war : location->Warriors())
		if (!war->Action()) {
			for (auto& arm : war->arms)
				if (arm != nullptr)
					if (_addArms(arm)) arm = nullptr;
			if (arms.size() == maxArmsNum) break;
		}
}

